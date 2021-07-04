if (isset($_GET['buy']))
  {
     checkvalue($_GET['buy']);
     $promos = array(
             'DNIDEBINY2021' => array('day' => '2021-06-01', 'armId' => '1'),
     );
     $multiplier = 0.75;
     $arm = $db -> Execute("SELECT * FROM equipment WHERE id=".$_GET['buy']);
     if ($arm -> fields['id'] == 0) 
       {
     message('error', NO_ITEM);
       }
     elseif ($arm -> fields['status'] != 'S') 
       {
     message('error', BAD_STATUS);
       }
     elseif ($arm -> fields['cost'] > $player -> credits && !isset($_GET['promo'])) 
       {
            message('error', NO_MONEY);
       } 
     else
       {
     $validPromo = False;
         if(isset($_GET['promo'])) {
         $today = date("Y-m-d");
         if(strlen($_GET['promo']) > 0 && $today !== $promos[$_GET['promo']]['day']) {
            message('error', PROMO_EXPIRED);
         } 
         elseif($_GET['buy'] == $promos[$_REQUEST['promo']]['armId']) {
            message('success', PROMO_VALID); 
            $validPromo = True; 
            $arm -> fields['cost'] = 0;
         } else {
            message('error', PROMO_INVALID);
         }
     }
     if(!isset($_GET['promo']) || $validPromo) { 
         $newcost = ceil($arm -> fields['cost'] * multiplier);
         $test = $db -> Execute("SELECT id FROM equipment WHERE name='".$arm -> fields['name']."' AND wt=".$arm -> fields['wt']." AND type='".$arm -> fields['type']."' AND status='U' AND owner=".$player -> id." AND power=".$arm -> fields['power']." AND zr=".$arm -> fields['zr']." AND szyb=".$arm -> fields['szyb']." AND maxwt=".$arm -> fields['maxwt']." AND poison=0 AND cost=".$newcost);
         if ($test -> fields['id'] == 0) 
           {
             $db -> Execute("INSERT INTO equipment (owner, name, power, type, cost, zr, wt, minlev, maxwt, amount, magic, szyb, lang, repair) VALUES(".$player -> id.",'".$arm -> fields['name']."',".$arm -> fields['power'].",'".$arm -> fields['type']."',".$newcost.",".$arm -> fields['zr'].",".$arm -> fields['wt'].",".$arm -> fields['minlev'].",".$arm -> fields['maxwt'].",1,'".$arm -> fields['magic']."',".$arm -> fields['szyb'].",'".$lang."', ".$arm -> fields['repair'].")");
           } 
         else 
           {
             $db -> Execute("UPDATE equipment SET amount=amount+1 WHERE id=".$test -> fields['id']);
           }
         $test -> Close();
         $db -> Execute("UPDATE players SET credits=credits-".$arm -> fields['cost']." WHERE id=".$player -> id);
         message('success', YOU_PAY.' <b>'.$arm->fields['cost'].'</b> '.AND_BUY.' <b>'.$arm->fields['name'].' '.I_POWER.' + '.$arm->fields['power'].'</b>.');
         $arm -> Close();
      }
        }
   }
