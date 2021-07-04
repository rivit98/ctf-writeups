function RandomString()
    {
        $characters = '0123456789abcdefghijklmnopqrstuvwxyz';
        $randstring = '';
        for ($i = 0; $i < 8; $i++) {
            $randstring = $randstring . $characters[rand(0, strlen($characters))];
        }
        return $randstring;
    }

if (isset($_GET['action']))
  {
    /**
     * Fight with other players
     */
    if ($_GET['action'] == 'showalive') 
      {
    $smarty -> assign ( array(
                  "Showinfo" => BATTLE_SHOWALIVE_INFO,
                  "Orback" => OR_BACK,
                  "Bback" => B_BACK));
      }
    
    /**
     * Fight with dummy
     */
    if ($_GET['action'] == 'dummy')
      {
     $fight = $_GET['fight'];
     checkvalue($fight);
     $fight = intval($fight);

     $randomString = RandomString();
     srand(hexdec(substr(md5($randomString + substr(time(), 0, 5)), 0, 8)));
     
     $win = rand();
     
     if($win === $fight)
       {
        $smarty -> assign( array(
            "Showinfo" => FIGHT_DUMMY_SUCCESS
        ));
         }
     else 
       {
         $smarty -> assign( array(
             "Showinfo" => FIGHT_DUMMY_FAIL
        ));
       }
      }
