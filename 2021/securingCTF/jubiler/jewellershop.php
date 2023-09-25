$strMessage = '';
$shopInfo = SHOP_INFO;
$objRings = $db -> Execute("SELECT `id`, `name`, `amount` FROM `rings`");
$ringPrice = 500;
$closed = False;
$i = 0;
$arrId = array();
$arrName = array();
$arrAmount = array();
while (!$objRings -> EOF)
{
    $arrId[$i] = $objRings -> fields['id'];
    $arrName[$i] = $objRings -> fields['name'];
    $arrAmount[$i] = $objRings -> fields['amount'];
    $i ++;
    $objRings -> MoveNext();
}
$objRings -> Close();

if(isset($_GET['craft'])) {
    $item = $_GET['craft'];
    extract($_GET);
    $material = $$item["material"];
    $inscription = $$item["inscription"];
    $result = craft($item, $material, $inscription);
    if(isset($result))
         $shopInfo = $result;
    else {
     $closed = True;
     $shopInfo = SHOP_CLOSED;
    }
}

/**
 * Buy rings
 */
if (isset($_GET['buy']) && !$closed)
{
    $_GET['buy'] = intval($_GET['buy']);
    if ($_GET['buy'] < 0 || $_GET['buy'] > 6)
      {
    error(ERROR);
      }
    if ($player -> credits < $ringPrice)
    {
        error(NO_MONEY);
    }
    $intKey = $_GET['buy'] - 1;
    if (!$arrAmount[$intKey])
    {
    // New delivery
        $db -> Execute("UPDATE `rings` SET `amount`=30 WHERE `id`=".$_GET['buy']);
    }
    $db -> Execute("UPDATE `rings` SET `amount`=`amount`-1 WHERE `id`=".$_GET['buy']);
    $objTest = $db -> Execute("SELECT `id` FROM `equipment` WHERE `owner`=".$player -> id." AND `name`='".$arrName[$intKey]."' AND `status`='U' AND `cost`=50");
    if (!$objTest -> fields['id'])
    {
    $newPrice = $ringPrice / 10;
        $db -> Execute("INSERT INTO `equipment` (`owner`, `name`, `power`, `status`, `type`, `cost`, `minlev`, `amount`) VALUES(".$player -> id.", '".$arrName[$intKey]."', '1', 'U', 'I'," . $newPrice . ", '1', '1')");
    }
        else
    {
        $db -> Execute("UPDATE `equipment` SET `amount`=`amount`+1 WHERE `id`=".$objTest -> fields['id']);
    }
    $objTest -> Close();
    $db -> Execute("UPDATE `players` SET `credits`=`credits`-" . $ringPrice . " WHERE `id`=".$player -> id);
    $strMessage = YOU_BUY . $arrName[$intKey] . FOR_A . $ringPrice . CURRENCY . "." . THANK_YOU . "<a href=\"jewellershop.php\">".A_REFRESH."</a>";
}
