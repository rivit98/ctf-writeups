# corCTF 2021, CShell, pwn

## Description
My friend Hevr thinks I can't code, so I decided to prove him wrong by making a restricted shell in which he is unable to play squad. I must add that my programming skills are very cache money...

## Solution

Heap challenge. Our target is logging as root.

```c
void bash(){
	if (uid == 0){
		system("bash");
	}
	else 
	{
		puts("Who do you think you are?");
		exit(0);
	}
}
```
We have to somehow set uid to zero. Is it only set inside `logout` function:

```c
void logout(){
	fflush(stdin);
	getchar();
	struct tracker *ptr;
	printf("Username:");
	char username_l[9];
	char password_l[32];
	char *hash;
	scanf("%8s",username_l);
	for (ptr = root_t; ptr != NULL; ptr = root_t->next) {
        if (strcmp(ptr->name, username_l) == 0) { 
		printf("Password:");
	    scanf("%32s",password_l);
	    hash = crypt(password_l,salt);
	    if (strcmp(hash,ptr->ptr->passwd) == 0){
		    strcpy(username,ptr->name);
		    uid = ptr->id;
		    puts("Authenticated!");
		    menu();
	    }
```
If we somehow can overwrite root password with our value then we can log in and get the shell. There is suspicious fragment of code inside `setup` function:

```c
	scanf("%d",&length);
	userbuffer = malloc(length + 8);
	printf("Great, please type your bio.\n> ");
	getchar();
	fgets((userbuffer + 8),201,stdin);
```

We can easily overflow the allocated chunk of memory. Looking more at the code we can notice that there are only two `free` calls. So It is probably about tcache mechanism.
After some debugging we can easily trigger alocation of chunk before root user structure and overflow it's password with known value. 


Solve script: [solve.py](./solve.py)

Flag: corctf{tc4ch3_r3u5e_p1u5_0v3rfl0w_equ4l5_r007}
