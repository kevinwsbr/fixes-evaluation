<?php
if(!defined('sugarEntry') || !sugarEntry) die('Not A Valid Entry Point');
/*********************************************************************************
 * SugarCRM Community Edition is a customer relationship management program developed by
 * SugarCRM, Inc. Copyright (C) 2004-2013 SugarCRM Inc.

 * SuiteCRM is an extension to SugarCRM Community Edition developed by Salesagility Ltd.
 * Copyright (C) 2011 - 2014 Salesagility Ltd.
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Affero General Public License version 3 as published by the
 * Free Software Foundation with the addition of the following permission added
 * to Section 15 as permitted in Section 7(a): FOR ANY PART OF THE COVERED WORK
 * IN WHICH THE COPYRIGHT IS OWNED BY SUGARCRM, SUGARCRM DISCLAIMS THE WARRANTY
 * OF NON INFRINGEMENT OF THIRD PARTY RIGHTS.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Affero General Public License along with
 * this program; if not, see http://www.gnu.org/licenses or write to the Free
 * Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301 USA.
 *
 * You can contact SugarCRM, Inc. headquarters at 10050 North Wolfe Road,
 * SW2-130, Cupertino, CA 95014, USA. or at email address contact@sugarcrm.com.
 *
 * The interactive user interfaces in modified source and object code versions
 * of this program must display Appropriate Legal Notices, as required under
 * Section 5 of the GNU Affero General Public License version 3.
 *
 * In accordance with Section 7(b) of the GNU Affero General Public License version 3,
 * these Appropriate Legal Notices must retain the display of the "Powered by
 * SugarCRM" logo and "Supercharged by SuiteCRM" logo. If the display of the logos is not
 * reasonably feasible for  technical reasons, the Appropriate Legal Notices must
 * display the words  "Powered by SugarCRM" and "Supercharged by SuiteCRM".
 ********************************************************************************/


require_once('include/JSON.php');
require_once('include/entryPoint.php');
require_once 'include/upload_file.php';

global $sugar_config;
$supportedExtensions = array('jpg', 'png', 'jpeg');
$json = getJSONobj();
$rmdir=true;
$returnArray = array();
if($json->decode(html_entity_decode($_REQUEST['forQuotes']))){
    $returnArray['forQuotes']="quotes";
}else{
    $returnArray['forQuotes']="company";
}
if(isset($_FILES['file']) && !empty($_FILES['file']['name'])) {
    $filename = $_FILES['file']['name'];
    $fileExtension = strtolower(pathinfo($filename, PATHINFO_EXTENSION));
    if(in_array($fileExtension, $supportedExtensions)) {
        $fileTempName = $_FILES['file']['tmp_name'];
        $fileDestination = sugar_cached('images/' . uniqid() . '.' . $fileExtension);
        if(move_uploaded_file($fileTempName, $fileDestination)) {
            $img_size = getimagesize($fileDestination);
            $filetype = $img_size['mime'];
            $test = $img_size[0] / $img_size[1];
            if (($test > 10 || $test < 1) && $returnArray['forQuotes'] == 'company') {
                $rmdir = false;
                $returnArray['data'] = 'size';
            }
            if (($test > 20 || $test < 3) && $returnArray['forQuotes'] == 'quotes')
                $returnArray['data'] = 'size';
            copy($fileDestination, $fileDestination);
        } else {
            $returnArray['data'] = 'file_error';
        }
    } else {
        $returnArray['data'] = 'invalid_extension';
    }
} else {
    $returnArray['data'] = 'no_file_uploaded';
}

if(!empty($returnArray['data'])) {
    echo $json->encode($returnArray);
} else {
    $rmdir = false;
    $returnArray['data'] = 'ok';
    echo $json->encode($returnArray);
}

sugar_cleanup();
exit();
