<?php
/*
if (array_key_exists('img',$_REQUEST)) {
    echo $_REQUEST['img'];

    // decode the base64-encoded image received
    // drop the first 22 characters from the string received,
    // (having the substring "data:image/png;base64,")
    $imgData = base64_decode(substr($_REQUEST['img'],22));

    // Path where the image is going to be saved
    $file = '/photos/image.png';

    // delete previously uploaded image with the same path
    if (file_exists($file)) { unlink($file); }

        // write $imgData into the file
        $fp = fopen($file, 'w');
        fwrite($fp, $imgData);
        fclose($fp);
}
*/


    $data = $_POST['img'];
    $number = $_POST['drawnumber'];
    list($type, $data) = explode(';', $data);
    list(, $data)      = explode(',', $data);

    //$data = str_replace(' ','+',$data);
  //$decocedData = base64_decode($encodedData);

    $data = base64_decode($data);

    mkdir($_SERVER['DOCUMENT_ROOT'] . "/dataset-images/");

    file_put_contents($_SERVER['DOCUMENT_ROOT'] . "/dataset-images/".$number."_".time().'.png', $data);
    die;

?>
