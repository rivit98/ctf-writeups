/**
 * Read selected message/topic
 */
if (isset ($_GET['read'])) 
{
    checkvalue($_GET['read']);
    $intReceiver = 0;
    $db -> Execute("UPDATE `mail` SET `unread`='T' WHERE `topic`=".$_GET['read']." AND `owner`=".$player->id);
    $arrSender = array();
    $arrSenderid = array();
    $arrMid = array();
    $arrBody = array();
    $arrDate = array();

    if (!isset($_GET['one']))
      {
    //Pagination
    $objAmount = $db->Execute("SELECT count(`id`) FROM `mail` WHERE `owner`=".$player->id.$strQuery." AND `topic`=".$_GET['read']);
    $intPages = ceil($objAmount->fields['count(`id`)'] / 20);
    $objAmount->Close();
    if (!isset($intPage))
      {
        $intPage = $intPages;
      }
    
    $objMails = $db->SelectLimit("SELECT * FROM `mail` WHERE `topic`=".$_GET['read']." AND `owner`=".$player->id." ORDER BY `id` ASC", 20, 20 * ($intPage - 1));
    $_GET['one'] = 0;
      }
    else
      {
    $intPage = 0;
    $intPages = 0;
    $objMails = $db->Execute("SELECT * FROM `mail` WHERE `id`=".$_GET['read']);
    $_GET['one'] = 1;
      }
    if (!$objMails->fields['id'])
      {
    error("Nie ma takiej wiadomości.");
      }
    $strSubject = $objMails->fields['subject'];
    while (!$objMails->EOF)
      {
    if ($intReceiver == 0)
      {
        if ($objMails->fields['senderid'] != $player->id)
          {
        $intReceiver = $objMails->fields['senderid'];
          }
        elseif ($objMails->fields['to'] != $player->id)
          {
        $intReceiver = $objMails->fields['to'];
          }
      }
    $arrSender[] = $objMails->fields['sender'].' (nieobecny(a))';
    $arrSenderid[] = $objMails->fields['senderid'];
    $arrMid[] = $objMails->fields['id'];
    $arrBody[] = $objMails->fields['body'];
    $arrDate[] = T_DAY.$objMails->fields['date'];
    $objMails->MoveNext();
      }    
    $objPeople = $db->Execute("SELECT `id`, `user`, `tribe` FROM `players` WHERE `id` IN (".implode(',', $arrSenderid).");") or die($db->ErrorMsg());
    $arrNames = array();
    while (!$objPeople->EOF)
      {
    $arrNames[$objPeople->fields['id']] = $arrTags[$objPeople->fields['tribe']][0]." ".$objPeople->fields['user']." ".$arrTags[$objPeople->fields['tribe']][1].' (ID: '.$objPeople->fields['id'].')';
    $objPeople->MoveNext();
      }
    for ($i = 0; $i < count($arrSenderid); $i++)
      {
    if (array_key_exists($arrSenderid[$i], $arrNames))
      {
        $arrSender[$i] = $arrNames[$arrSenderid[$i]];
      }
      }
    $objPeople->Close();
    $objMails->Close();
    $smarty -> assign(array("Senders" => $arrSender,
                "Sendersid" => $arrSenderid,
                "Mailsid" => $arrMid,
                "Bodies" => $arrBody,
                "Date2" => $arrDate,
                "Mtopic" => $_GET['read'],
                "Receiver" => $intReceiver,
                "Subject" => $strSubject,
                "One" => $_GET['one'],
                            "Asave" => A_SAVE,
                            "Adelete" => A_DELETE,
                            "Twrite" => T_WRITE,
                            "Asend2" => A_SEND,
                            "Ablock" => A_BLOCK,
                "Asaved" => "Oznaczone",
                "Amail" => "Poczta",
                "Topic" => "Temat",
                "Asend" => "Odpisz",
                "Tpages" => $intPages,
                "Tpage" => $intPage,
                "Fpage" => "Idź do strony:",
                "Body" => '',
                "Abold" => "Pogrubienie",
                "Aitalic" => "Kursywa",
                "Aunderline" => "Podkreślenie",
                "Aemote" => "Emocje/Czynność",
                "Ocolors" => array("red" => "czerwony",
                           "green" => "zielony",
                           "white" => "biały",
                           "yellow" => "żółty",
                           "blue" => "niebieski",
                           "aqua" => "cyjan",
                           "fuchsia" => "fuksja",
                           "grey" => "szary",
                           "lime" => "limonka",
                           "maroon" => "wiśniowy",
                           "navy" => "granatowy",
                           "olive" => "oliwkowy",
                           "purple" => "purpurowy",
                           "silver" => "srebrny",
                           "teal" => "morski"),
                "Acolor" => "Kolor",
                "Acenter" => "Wycentrowanie",
                "Aquote" => "Cytat",
                "Mhelp" => "Linki automatycznie zamieniane są na klikalne. Możesz używać następujących znaczników BBCode:<br /><ul><li>[b]<b>Pogrubienie</b>[/b]</li><li>[i]<i>Kursywa</i>[/i]</li><li>[u]<u>Podkreślenie</u>[/u]</li><li>[color (angielska nazwa koloru (red, yellow, itp) lub kod HTML (#FFFF00, itp)]pokolorowanie tekstu[/color]</li><li>[center]wycentrowanie tekstu[/center]</li><li>[quote]cytat[/quote]</ul>"));
}
