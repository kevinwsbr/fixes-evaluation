<?php
if(!defined('sugarEntry') || !sugarEntry) die('Not A Valid Entry Point');
require_once('include/entryPoint.php');
require_once 'include/upload_file.php';

global $sugar_config;
$supportedExtensions = array('jpg', 'png', 'jpeg');
$rmdir = true;
$returnArray = array();
if(json_decode($_REQUEST['forQuotes'])){
    $returnArray['forQuotes']="quotes";
}else{
    $returnArray['forQuotes']="company";
}
$upload_ok = false;
$upload_path = 'tmp_logo_' . $returnArray['forQuotes'] . '_upload';
if(isset($_FILES['file_1'])){
    $upload = new UploadFile('file_1');
    if($upload->checkExtension($supportedExtensions)){ // Validate file extension
        if($upload->moveUploadedFile($upload_path)){ // Move uploaded file to directory
            $file_name = $upload_path . '/' . $upload->getFileName();
            if(file_exists($file_name) && is_file($file_name)) {
                $encoded_file_name = rawurlencode($upload->getFileName());
                $returnArray['path'] = $upload_path . '/' . $encoded_file_name;
                $returnArray['url']= 'cache/images/'.$encoded_file_name;
                if(!verify_uploaded_image($file_name, $returnArray['forQuotes'] == 'quotes')) {
                    $returnArray['data']='other';
                    $returnArray['path'] = '';
                } else {
                    $img_size = getimagesize($file_name);
                    if(!$img_size){ // Handle error if getimagesize fails
                        $returnArray['data']='image_error';
                    }else{
                        $test=$img_size[0]/$img_size[1];
                        if (($test>10 || $test<1) && $returnArray['forQuotes'] == 'company'){
                            $rmdir=false;
                            $returnArray['data']='size';
                        }
                        if (($test>20 || $test<3)&& $returnArray['forQuotes'] == 'quotes')
                            $returnArray['data']='size';
                    }
                }
                if(!empty($returnArray['data'])){
                    echo json_encode($returnArray); // Use built-in json_encode function
                }else{
                    $rmdir=false;
                    $destination = sugar_cached('images/'.$upload->getFileName());
                    if(!copy($file_name, $destination)){ // Handle error if copy fails
                        $returnArray['data']='copy_error';
                        echo json_encode($returnArray);
                    }else{
                        $returnArray['data']='ok';
                        echo json_encode($returnArray);
                    }
                }
            }else{
                $returnArray['data']='file_error';
                echo json_encode($returnArray);
            }
        }else{
            $returnArray['data']='move_error';
            echo json_encode($returnArray);
        }
    }else{
        $returnArray['data']='invalid_extension';
        echo json_encode($returnArray);
    }
}
sugar_cleanup();
exit();
