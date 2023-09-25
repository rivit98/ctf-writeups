# PicoCTF 2021, Scrambled RSA, crypto

## Description
Check out my new video-game and spaghetti-eating streaming channel on Twixer!

## Solution

After quick analysis of the source code we see obvious target:
```c
void hahaexploitgobrrr(){
```

We have to run this function, we can get address of this function by calling:
```c
void s(){
 	printf("OOP! Memory leak...%p\n", hahaexploitgobrrr);
 	puts("Thanks for subsribing! I really recommend becoming a premium member!");
}
```

We can steal code execution flow by overwriting pointer whatToDo in the following struct:

```c
typedef struct {
	uintptr_t (*whatToDo)();
	char *username;
} cmd;
```

We do this by logging out (function i()) and leaving message. This is possible because malloc in leaveMessage function will return block of memory which was occupied by `cmd` struct. As message we should pass hahaexploitgobrrr() function pointer because it will act as whatToDo pointer in `cmd` struct.


Solve: [rsa.py](./rsa.py)

