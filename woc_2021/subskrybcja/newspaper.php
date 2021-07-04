/**
* Read and edit newspaper
*/
if ((isset($_GET['step']) && $_GET['step'] == 'new') || (isset($_GET['read']) || (isset($_GET['step3']) && $_GET['step3'] == 'S')))
{
    $subscription = False;
    $secretCode = $_COOKIE["subscription"];
    if(md5($secretCode) == "0e938153791264385292992237641232") {
        $subscription = True;
    }
    if(!$subscription) {
    echo(NO_SUBSCRIPTION);
    } else {
    echo(NEWSPAPER_CONTENT);
    }
}
