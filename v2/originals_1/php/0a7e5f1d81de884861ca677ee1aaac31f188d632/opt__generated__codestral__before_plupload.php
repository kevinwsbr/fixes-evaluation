 // Handle uploaded file
    if (empty($_FILES['file']) || $_FILES['file']['error'] !== UPLOAD_ERR_OK) {
        throw new UploadException(isset($_FILES['file']['error']) ? $_FILES['file']['error'] : 0);
    }

    $chunkIndex = isset($_REQUEST["chunk"]) ? intval($_REQUEST["chunk"]) : 0;
    $chunkCount = isset($_REQUEST["chunks"]) ? intval($_REQUEST["chunks"]) : 1;
    //$chunkSize = isset($_SERVER['CONTENT_LENGTH']) ? intval($_SERVER['CONTENT_LENGTH']) : 0;
    $chunkSize = isset($_FILES['file']['size']) ? intval($_FILES['file']['size']) : 0;
    $totalSize = isset($_REQUEST["picturesize"]) ? intval($_REQUEST["picturesize"]) : $chunkSize;

    if (isset($_REQUEST["name"])) {
        $fileName = $_REQUEST["name"];
    } elseif (!empty($_FILES['file']['name'])) {
        $fileName = $_FILES['file']['name'];
    } else {
        throw new UploadException(UPLOAD_ERR_NO_FILE);
    }

    if (isset($settings['max_file_size']) and intval($settings['max_file_size']) > 0) {
        $maxFileSize = intval($settings['max_file_size']);
        if ($totalSize > $maxFileSize) {
            @unlink($_FILES["file"]["tmp_name"]);
            die('{"jsonrpc" : "2.0", "error" : {"code": 103, "message": "File is too large"}, "id" : "id"}');
        }
    }

    //$uploadedFile = $_FILES["file"]["tmp_name"];
    $uploadedFile = mw()->files->move_uploaded_file($_FILES['file']['tmp_name'], $_FILES['file']['name']);

    if (!is_uploaded_file($uploadedFile)) {
        throw new UploadException(UPLOAD_ERR_CANT_WRITE);
    }

    $savePath = mw()->files->uploads_dir();
    if (empty($savePath) || !mw()->files->is_writable($savePath)) {
        @unlink($uploadedFile);
        throw new UploadException(UPLOAD_ERR_CANT_WRITE);
    }

    $targetFile = rtrim($savePath, '/') . '/' . ltrim($_REQUEST["name"], '/');

    if ($chunkCount > 1) {
        // Save the partial content to a temporary file
        if (!move_uploaded_file($uploadedFile, $targetFile)) {
            throw new UploadException(UPLOAD_ERR_CANT_WRITE);
        }

        if ($chunkIndex < $chunkCount - 1) {
            // More chunks to follow
            echo json_encode(['success' => true]);
            exit;
        }
    } else {
        if (!move_uploaded_file($uploadedFile, $targetFile)) {
            throw new UploadException(UPLOAD_ERR_CANT_WRITE);
        }
    }

    // Combine chunks into a single file if necessary
    if ($chunkCount > 1) {
        $output = @fopen($targetFile, 'wb');
        if (!$output) {
            throw new UploadException(UPLOAD_ERR_CANT_WRITE);
        }

        for ($i = 0; $i < $chunkCount; $i++) {
            $chunkPath = rtrim($savePath, '/') . '/' . ltrim($_REQUEST["name"], '/') . '.part' . $i;
            if (!file_exists($chunkPath)) {
                @fclose($output);
                throw new UploadException(UPLOAD_ERR_CANT_WRITE);
            }

            $input = fopen($chunkPath, 'rb');
            if (!$input) {
                @fclose($output);
                throw new UploadException(UPLOAD_ERR_CANT_WRITE);
            }

            while ($data = fread($input, 8192)) {
                fwrite($output, $data);
            }

            fclose($input);
            unlink($chunkPath);
        }

        fclose($output);
    }