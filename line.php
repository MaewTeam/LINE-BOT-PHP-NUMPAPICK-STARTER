 
<?php
function send_LINE($msg){
 // token from line api
 $access_token = 'IkA0NfE3wTrE7lxdnwE2DFgyAWpvOtTMTsXlNt96hJSIBtY/CZF/Tyoaa9rb2cCWqEvbWkN2o8mvlqryWqKOkaagtybWV1/KnI13+qhCBuC8o0n3ZYbvF4g254TeJivbFmnIBKl/c+wT7bP+RekmjwdB04t89/1O/w1cDnyilFU='; 
 
 $content = file_get_contents('php://input');
 $arrayJson = json_decode($content, true);
 $arrayHeader = array();
 $arrayHeader[] = "Content-Type: application/json";
 $arrayHeader[] = "Authorization: Bearer {$access_token}";
 
 $message = $arrayJson['events'][0]['message']['text'];
 $id = $arrayJson['events'][0]['source']['userId'];
 if($message == "m1"){
       for($i=1;$i<=10;$i++){
          $arrayPostData['to'] = $id;
          $arrayPostData['messages'][0]['type'] = "text";
          $arrayPostData['messages'][0]['text'] = $i;
          pushMsg($arrayHeader,$arrayPostData);
       }
  }
 
 $messages = [
        'type' => 'text',
        'text' => $msg
        //'text' => $text
      ];

      // Make a POST Request to Messaging API to reply to sender
      $url = 'https://api.line.me/v2/bot/message/push'; 
      $data = [

        'to' => '7cae6d4c3810f294802285d6ccd82a77',  // key serect from line api
        'messages' => [$messages],
      ];
      $post = json_encode($data);
      $headers = array('Content-Type: application/json', 'Authorization: Bearer ' . $access_token);

      $ch = curl_init($url);
      curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "POST");
      curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
      curl_setopt($ch, CURLOPT_POSTFIELDS, $post);
      curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);
      curl_setopt($ch, CURLOPT_FOLLOWLOCATION, 1);
      $result = curl_exec($ch);
      curl_close($ch);

      echo $result . "\r\n"; 
}

function pushMsg($arrayHeader,$arrayPostData){
      $strUrl = "https://api.line.me/v2/bot/message/push";
      $ch = curl_init();
      curl_setopt($ch, CURLOPT_URL,$strUrl);
      curl_setopt($ch, CURLOPT_HEADER, false);
      curl_setopt($ch, CURLOPT_POST, true);
      curl_setopt($ch, CURLOPT_HTTPHEADER, $arrayHeader);
      curl_setopt($ch, CURLOPT_POSTFIELDS, json_encode($arrayPostData));
      curl_setopt($ch, CURLOPT_RETURNTRANSFER,true);
      curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
      $result = curl_exec($ch);
      curl_close ($ch);
   }
   exit;
?>
