import os

from Crypto.Util.number import getPrime, bytes_to_long


def pad(data, bitsize):
    missing = (bitsize - len(data) * 8) // 8
    return os.urandom(missing // 2) + data + os.urandom(missing // 2)


def main():
    p = getPrime(1024)
    q = getPrime(1024)
    N = p * q
    e1 = getPrime(32)
    e2 = getPrime(32)
    assert p != q
    assert e1 != e2

    m = bytes_to_long(pad(open("flag.txt", 'rb').read(), 2047))
    c1 = pow(m, e1, N)
    c2 = pow(m, e2, N)
    print(f'N = {N}')
    print(f'e1 = {e1}')
    print(f'e2 = {e2}')
    print(f'c1 = {c1}')
    print(f'c2 = {c2}')


main()


# N = 15283309577603488890133274107897750430930844441662363425468092206031400480287948452316263289981045745358293847045364808152434120078371778195296980052545240351067778903705170874986003108660955660114746872779032949110187522223624472790599853828654567297437606366492432019446893183534352480229224086632734193992222009505535404175815277741035597204410072449952314161289208873568000139928514189869860934750176357542041239874536162900747761185172632844490483062347848937021140996302924761883195198472667271848058091138689964771115608974093866818443591683308495902615298801798333924335400385736563372190819155179730196410201
# e1 = 3791335447
# e2 = 2572511867
# c1 = 8638899850921773212005829853690607732687373134541407139517280676856550616567432120866090405974052051180222166170366712696237514108663592355665834150784120748691937179988330174151668042283748171869766268787902240737031396132674399375504934228003423637227278765723465401581885049147383406207756443896957407853444856849836692273897221572621643143935797216459394888115523570572588106430391163826886382863257107332042686555536950267473620034812005032747616871849480439234230636888139185882063911539787951450933711832204382666917747070923766091315076950655333150384005190481028844335067896975307558495625052437887128031182
# c2 = 7944512764135228535928475390070897032164151091017260910652962028605559227044483213843695473107050544251964969015209639947241923366367593635143020355115430433157453038105291806447500373182202580172787722309259901773437911671572370694439734600069607974329643035534973692147295417629600001808707134112120867648527467850066174494083532406292395073055602396601764859230814365275297366048508884801750768912680989173220632872592955295305073574963345333388690413344139921601588396742118287466329881052275120793808515262818454598339948560285866996354627925766642992207718197562207559961901419993930328131061273076141783533884