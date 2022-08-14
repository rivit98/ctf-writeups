# European Cyber Security Challenge Eliminations 2021, Login system, web

## Description
Just a login system. Nothing extraordinary.

## Solution

After visiting https://login-system.ecsc21.hack.cert.pl/ we see the login form with the footer of the commit hash the application is built from. 
Accessing https://login-system.ecsc21.hack.cert.pl/.git/HEAD ends up with HEAD file being downloaded. Using git-dumper allows us to dump git repository and browse the code.

In one of the python file we see:
```py
# TODO change when deploying to production
app.config['SECRET_KEY'] = b"\xCC" * 16
```

so we can run the app locally, generate admin session key and visit /user to get the flag.

Flag: `ecsc21{OH_NO__diz_weak_session_secretz}`