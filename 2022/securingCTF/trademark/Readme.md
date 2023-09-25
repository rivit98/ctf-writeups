# CursedNova, Trademark, network 

## Description

Our law deparment already prepared the papers for trademark registration. Soon, we will be able to use the CursedNova™! We need to hurry and register the proper domains. We already registered cursednova.PL, but there will be many more! TLDr: go for it!

## Solution

So looks like we have to find the proper domains. I used domains.google.com and it showed me that these domains are taken: `cursednova.space` and `cursednova.fun`. Using `dig` on these hostnames we got:

```
→ /media/sf_D_DRIVE$ dig +noall +answer +multiline cursednova.fun any
cursednova.fun.		300 IN A 0.6.6.6
cursednova.fun.		21600 IN NS ns-1515.awsdns-61.org.
cursednova.fun.		21600 IN NS ns-1644.awsdns-13.co.uk.
cursednova.fun.		21600 IN NS ns-25.awsdns-03.com.
cursednova.fun.		21600 IN NS ns-659.awsdns-18.net.
cursednova.fun.		900 IN SOA ns-25.awsdns-03.com. awsdns-hostmaster.amazon.com. (
				1          ; serial
				7200       ; refresh (2 hours)
				900        ; retry (15 minutes)
				1209600    ; expire (2 weeks)
				86400      ; minimum (1 day)
				)
cursednova.fun.		300 IN TXT "\"You are on the right track!\" - _o__ f_  t__ s__d__a__s"
```

```
→ /media/sf_D_DRIVE$ dig +noall +answer +multiline cursednova.space any
cursednova.space.	300 IN A 0.6.6.6
cursednova.space.	21600 IN NS ns-124.awsdns-15.com.
cursednova.space.	21600 IN NS ns-1274.awsdns-31.org.
cursednova.space.	21600 IN NS ns-1994.awsdns-57.co.uk.
cursednova.space.	21600 IN NS ns-641.awsdns-16.net.
cursednova.space.	900 IN SOA ns-124.awsdns-15.com. awsdns-hostmaster.amazon.com. (
				1          ; serial
				7200       ; refresh (2 hours)
				900        ; retry (15 minutes)
				1209600    ; expire (2 weeks)
				86400      ; minimum (1 day)
				)
cursednova.space.	300 IN TXT "\"You are on the right track!\" - l__k __r __e __b__m__n_"
```

merging two set of letters we got
```
_o__ f_  t__ s__d__a__s
l__k __r __e __b__m__n_

lo_k f_r t_e s_bd_ma_ns
```

which means `look for the subdomains`

But as we see, I did't found all of the domains, so using ton of different webpages I finally found `cursednova.click`.

```
→ /media/sf_D_DRIVE$ dig +noall +answer +multiline cursednova.click txt
cursednova.click.	300 IN TXT "\"You are on the right track!\" - __o_ _o_ _h_ _u__o__i__"
```

Now we have full set of domains. Time to brute force the subdomains using `gobuster`, didn't have a time to finish the chall...


Flag: `CURSEDNOVA{7h3_70m_w41k32}`