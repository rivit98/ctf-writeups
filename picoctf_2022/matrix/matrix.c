__int64 __fastcall main(int a1, char **a2, char **a3)
{
  void *v3; // r13 
  char *v4; // r12
  __int16 *v5; // rsi
  char *v6; // rdi
  __int64 result; // rax
  void (*v8)(void); // rdx
  FILE *v9; // rbp
  __int16 out[2]; // [rsp+Ch] [rbp-16Ch] BYREF
  vmctx ctx; // [rsp+10h] [rbp-168h] BYREF
  char s[264]; // [rsp+40h] [rbp-138h] BYREF
  unsigned __int64 v13; // [rsp+148h] [rbp-30h]

  v13 = __readfsqword(0x28u);
  setvbuf(stdout, 0LL, 1, 0x2000uLL);
  v3 = malloc(0x800uLL);
  v4 = (char *)malloc(0x800uLL);
  ctx.bytecode = (__int64)&unk_20F0;
  ctx.pc = 0;
  *(__m128i *)&ctx.stack = _mm_unpacklo_epi64((__m128i)(unsigned __int64)v3, (__m128i)(unsigned __int64)v4);
  *(__m128i *)&ctx.getc = _mm_unpacklo_epi64((__m128i)(unsigned __int64)getc_0, (__m128i)(unsigned __int64)putc_0);
  do
    v5 = out;
  while ( (unsigned __int8)vm_step(&ctx, (__int64)out) );
  free(v3);
  v6 = v4;
  free(v4);
  if ( LOBYTE(out[0]) )
  {
    result = 0xFFFFFFFFLL;
  }
  else
  {
    if ( !out[1] )
    {
      puts("Have a flag!");
      v5 = (__int16 *)&qword_100;
      v9 = fopen("flag.txt", "r");
      fgets(s, 256, v9);
      fclose(v9);
      v6 = s;
      puts(s);
    }
    result = (unsigned __int16)out[1];
  }
  v8 = (void (*)(void))(v13 - __readfsqword(0x28u));
  if ( v8 )
    start((__int64)v6, (__int64)v5, v8);
  return result;
}

int sub_1320()
{
  return getc(stdin);
}

int __fastcall sub_1340(unsigned __int8 a1)
{
  return putc(a1, stdout);
}

__int64 __fastcall vm_step(vmctx *ctx, __int16 *out)
{
  _BYTE *bytecode; // rdi
  __int64 pc; // rax
  unsigned __int16 next_instr; // cx
  __int64 orig_pc; // rdx
  unsigned __int8 instr; // al
  __int16 *v8; // rax
  __int64 v9; // rdi
  __int64 result; // rax
  __int16 v11; // dx
  __int16 v12; // cx
  __int16 *v13; // rax
  __int16 *v14; // rax
  bool v15; // sf
  __int16 v16; // cx
  __int16 *stack; // rdx
  __int16 *v18; // rcx
  __int16 *v19; // rax
  __int16 v20; // dx
  __int16 *v21; // rax
  __int16 v22; // dx
  __int16 *v23; // rdx
  __int16 *mem2; // rax
  __int16 *v25; // rax
  __int16 v26; // dx
  __int16 *v27; // rdx
  __int16 *v28; // rax
  __int16 *v29; // rdx
  __int16 v30; // ax
  __int16 *v31; // rax
  bool v32; // zf
  __int16 *v33; // rax
  __int16 *v34; // rax
  bool v35; // cc
  __int16 *v36; // rax
  __int16 v37; // dx
  unsigned __int8 v38; // al
  __int16 *v39; // rdx

  bytecode = ctx->bytecode;
  pc = (unsigned __int16)ctx->pc;
  next_instr = pc + 1;
  orig_pc = pc;
  ctx->pc = pc + 1;
  instr = bytecode[pc];
  switch ( instr )
  {
    case 0u:
      return 1LL;
    case 1u:
      result = 0LL;
      if ( out )
      {
        stack = ctx->stack;
        *(_BYTE *)out = 0;
        v18 = stack - 1;
        LOWORD(stack) = *(stack - 1);
        ctx->stack = v18;
        out[1] = (__int16)stack;
      }
      return result;
    case 2u:
    case 3u:
    case 4u:
    case 5u:
    case 6u:
    case 7u:
    case 8u:
    case 9u:
    case 0xAu:
    case 0xBu:
    case 0xCu:
    case 0xDu:
    case 0xEu:
    case 0xFu:
    case 0x15u:
    case 0x16u:
    case 0x17u:
    case 0x18u:
    case 0x19u:
    case 0x1Au:
    case 0x1Bu:
    case 0x1Cu:
    case 0x1Du:
    case 0x1Eu:
    case 0x1Fu:
    case 0x22u:
    case 0x23u:
    case 0x24u:
    case 0x25u:
    case 0x26u:
    case 0x27u:
    case 0x28u:
    case 0x29u:
    case 0x2Au:
    case 0x2Bu:
    case 0x2Cu:
    case 0x2Du:
    case 0x2Eu:
    case 0x2Fu:
      goto halt_vm;
    case 0x10u:
      v25 = ctx->stack;
      v26 = *(v25 - 1);
      ctx->stack = v25 + 1;
      *v25 = v26;
      return 1LL;
    case 0x11u:
      --ctx->stack;
      return 1LL;
    case 0x12u:
      v36 = ctx->stack;
      v37 = *(v36 - 2) + *(v36 - 1);
      ctx->stack = v36 - 1;
      *(v36 - 2) = v37;
      return 1LL;
    case 0x13u:
      v19 = ctx->stack;
      v20 = *(v19 - 2) - *(v19 - 1);
      ctx->stack = v19 - 1;
      *(v19 - 2) = v20;
      return 1LL;
    case 0x14u:
      v21 = ctx->stack;
      v22 = *(v21 - 2);
      *(v21 - 2) = *(v21 - 1);
      ctx->stack = v21;
      *(v21 - 1) = v22;
      return 1LL;
    case 0x20u:
      v23 = ctx->stack - 1;
      ctx->stack = v23;
      LOWORD(v23) = *v23;
      mem2 = ctx->mem2;
      ctx->mem2 = mem2 + 1;
      *mem2 = (__int16)v23;
      return 1LL;
    case 0x21u:
      v27 = ctx->mem2 - 1;
      ctx->mem2 = v27;
      LOWORD(v27) = *v27;
      v28 = ctx->stack;
      ctx->stack = v28 + 1;
      *v28 = (__int16)v27;
      return 1LL;
    case 0x30u:
      v29 = ctx->stack - 1;
      v30 = *v29;
      ctx->stack = v29;
      ctx->pc = v30;
      return 1LL;
    case 0x31u:
      v31 = ctx->stack;
      v32 = *(v31 - 2) == 0;
      v16 = *(v31 - 1);
      ctx->stack = v31 - 2;
      if ( v32 )
        goto set_pc;
      return 1LL;
    case 0x32u:
      v33 = ctx->stack;
      v32 = *(v33 - 2) == 0;
      v16 = *(v33 - 1);
      ctx->stack = v33 - 2;
      if ( !v32 )
        goto set_pc;
      return 1LL;
    case 0x33u:
      v14 = ctx->stack;
      v15 = *(v14 - 2) < 0;
      v16 = *(v14 - 1);
      ctx->stack = v14 - 2;
      if ( !v15 )
        return 1LL;
      goto set_pc;
    case 0x34u:
      v34 = ctx->stack;
      v35 = *(v34 - 2) <= 0;
      v16 = *(v34 - 1);
      ctx->stack = v34 - 2;
      if ( !v35 )
        return 1LL;
set_pc:
      ctx->pc = v16;
      return 1LL;
    default:
      if ( instr == 0xC0 )
      {
        v38 = ((__int64 (__fastcall *)(_BYTE *, __int16 *, __int64))ctx->getc)(bytecode, out, orig_pc);
        v39 = ctx->stack;
        ctx->stack = v39 + 1;
        *v39 = v38;
        return 1LL;
      }
      if ( instr > 0xC0u )
      {
        if ( instr == 0xC1 )
        {
          v8 = ctx->stack;
          v9 = *((unsigned __int8 *)v8 - 2);
          ctx->stack = v8 - 1;
          ((void (__fastcall *)(__int64, __int16 *))ctx->putc)(v9, out);
          return 1LL;
        }
        goto halt_vm;
      }
      if ( instr == 0x80 )
      {
        v11 = orig_pc + 2;
        v12 = (char)bytecode[next_instr];
        goto LABEL_10;
      }
      if ( instr == 0x81 )
      {
        v11 = orig_pc + 3;
        v12 = *(_WORD *)&bytecode[next_instr];
LABEL_10:
        v13 = ctx->stack;
        ctx->pc = v11;
        ctx->stack = v13 + 1;
        *v13 = v12;
        return 1LL;
      }
halt_vm:
      result = 0LL;
      if ( out )
        *(_BYTE *)out = 1;
      return result;
  }
}
