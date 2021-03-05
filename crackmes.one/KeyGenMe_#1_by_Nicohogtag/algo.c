int __usercall sub_402448@<eax>(int a1@<ebx>, int (__userpurge *a2)@<eax>(int a1@<ebp>, int a2)@<ebp>, int a3@<edi>, int a4@<esi>)
{
  unsigned int v4; // esi
  int v5; // edx
  signed __int16 v6; // di
  int v7; // eax
  int v8; // ebx
  int v9; // eax
  void (__fastcall *v10)(_DWORD *, _DWORD *); // ebx
  int v11; // eax
  _DWORD *v12; // eax
  int v13; // ecx
  int v14; // eax
  int v15; // eax
  int v16; // eax
  _DWORD *v17; // eax
  int v18; // edx
  int v19; // eax
  int (__userpurge *v20)@<eax>(int@<ebp>, int); // edx
  int v21; // eax
  int v22; // eax
  int v23; // eax
  int v24; // eax
  _DWORD *v25; // eax
  int v26; // edx
  int v27; // eax
  int v28; // edx
  int v29; // ecx
  int v30; // eax
  int v31; // eax
  _DWORD *v32; // ebx
  int v33; // eax
  int v34; // ebx
  int v35; // eax
  int v36; // edx
  _DWORD *v37; // ebx
  int v38; // eax
  int v39; // eax
  int v40; // eax
  int v41; // ecx
  int v42; // eax
  int v43; // ebx
  int v44; // eax
  int v45; // ebx
  int v46; // eax
  int v47; // eax
  int v48; // eax
  int v49; // ecx
  int v50; // ebx
  int v51; // eax
  int v52; // eax
  int v53; // ebx
  int v54; // eax
  double v55; // st7
  char v56; // fps
  double v57; // st7
  int v58; // eax
  __int16 v59; // ax
  bool v60; // of
  __int16 v61; // ax
  double v62; // st7
  char v63; // fps
  int v67; // eax
  int v68; // eax
  double v69; // st7
  char v70; // fps
  int v74; // eax
  int v75; // eax
  double v76; // st7
  char v77; // fps
  int v81; // eax
  int v82; // eax
  __int16 v83; // di
  unsigned __int16 v84; // kr00_2
  __int16 v85; // di
  double v86; // st7
  char v87; // fps
  int v91; // eax
  int v92; // eax
  int v93; // eax
  int v94; // eax
  int v95; // eax
  int v96; // eax
  int v97; // eax
  int v98; // eax
  int v99; // eax
  int v100; // eax
  _DWORD *v101; // eax
  int v102; // edx
  int v103; // eax
  int v104; // eax
  int v105; // esi
  int v106; // eax
  int v107; // eax
  int v108; // eax
  int v109; // eax
  int v111; // [esp-1D8h] [ebp-1D8h] BYREF
  int v112; // [esp-1D4h] [ebp-1D4h]
  int v113; // [esp-1D0h] [ebp-1D0h]
  double v114; // [esp-1CCh] [ebp-1CCh]
  int v115; // [esp-1C4h] [ebp-1C4h]
  double v116; // [esp-1C0h] [ebp-1C0h]
  int v117; // [esp-1B8h] [ebp-1B8h]
  double v118; // [esp-1B4h] [ebp-1B4h]
  int v119; // [esp-1ACh] [ebp-1ACh]
  double v120; // [esp-1A8h] [ebp-1A8h]
  int v121; // [esp-1A0h] [ebp-1A0h]
  double v122; // [esp-19Ch] [ebp-19Ch]
  int v123; // [esp-194h] [ebp-194h]
  int v124; // [esp-184h] [ebp-184h]
  _DWORD v125[4]; // [esp-174h] [ebp-174h] BYREF
  _DWORD v126[5]; // [esp-164h] [ebp-164h] BYREF
  int v127; // [esp-150h] [ebp-150h]
  _DWORD *v128; // [esp-148h] [ebp-148h]
  _DWORD v129[2]; // [esp-134h] [ebp-134h] BYREF
  int v130; // [esp-12Ch] [ebp-12Ch]
  _DWORD v131[2]; // [esp-124h] [ebp-124h] BYREF
  int *v132; // [esp-11Ch] [ebp-11Ch]
  _DWORD v133[2]; // [esp-114h] [ebp-114h] BYREF
  int v134; // [esp-10Ch] [ebp-10Ch]
  _DWORD v135[4]; // [esp-104h] [ebp-104h] BYREF
  _DWORD v136[4]; // [esp-F4h] [ebp-F4h] BYREF
  _DWORD v137[2]; // [esp-E4h] [ebp-E4h] BYREF
  int v138; // [esp-DCh] [ebp-DCh]
  _DWORD v139[2]; // [esp-D4h] [ebp-D4h] BYREF
  int v140; // [esp-CCh] [ebp-CCh]
  _DWORD v141[2]; // [esp-C4h] [ebp-C4h] BYREF
  int v142; // [esp-BCh] [ebp-BCh]
  _DWORD v143[2]; // [esp-B4h] [ebp-B4h] BYREF
  int v144; // [esp-ACh] [ebp-ACh]
  int v145; // [esp-A4h] [ebp-A4h] BYREF
  int v146; // [esp-A0h] [ebp-A0h] BYREF
  int v147; // [esp-9Ch] [ebp-9Ch] BYREF
  int (__userpurge *v148)@<eax>(int@<ebp>, int); // [esp-98h] [ebp-98h] BYREF
  _DWORD v149[4]; // [esp-94h] [ebp-94h] BYREF
  _DWORD v150[4]; // [esp-84h] [ebp-84h] BYREF
  _DWORD v151[4]; // [esp-74h] [ebp-74h] BYREF
  int v152; // [esp-64h] [ebp-64h]
  _DWORD v153[4]; // [esp-60h] [ebp-60h] BYREF
  int v154; // [esp-50h] [ebp-50h] BYREF
  _DWORD v155[2]; // [esp-4Ch] [ebp-4Ch] BYREF
  int v156; // [esp-44h] [ebp-44h] BYREF
  _DWORD v157[4]; // [esp-40h] [ebp-40h] BYREF
  _DWORD v158[6]; // [esp-30h] [ebp-30h] BYREF
  int *v159; // [esp-18h] [ebp-18h]
  int *v160; // [esp-14h] [ebp-14h]
  _DWORD *v161; // [esp-10h] [ebp-10h]
  int (__userpurge *v162)@<eax>(int@<ebp>, int); // [esp-Ch] [ebp-Ch]
  int v163; // [esp-8h] [ebp-8h]
  unsigned int v164; // [esp-4h] [ebp-4h]

  v164 -= 71;
  v162 = a2;
  v158[5] = &_vbaExceptHandler;
  v158[4] = NtCurrentTeb()->NtTib.ExceptionList;
  v113 = a1;
  v112 = a4;
  v111 = a3;
  v159 = &v111;
  v160 = dword_401108;
  v161 = (v164 & 1);
  v164 &= 0xFFFFFFFE;
  v4 = v164;
  (*(*v4 + 4))(v4, a3, v112, a1);
  v5 = *v4;
  v6 = 0;
  v158[0] = 0;
  v157[0] = 0;
  v156 = 0;
  v155[0] = 0;
  v154 = 0;
  v153[0] = 0;
  v151[0] = 0;
  v150[0] = 0;
  v149[0] = 0;
  v148 = 0;
  v147 = 0;
  v146 = 0;
  v145 = 0;
  v143[0] = 0;
  v141[0] = 0;
  v139[0] = 0;
  v137[0] = 0;
  v136[0] = 0;
  v135[0] = 0;
  v133[0] = 0;
  v131[0] = 0;
  v129[0] = 0;
  v126[0] = 0;
  v125[0] = 0;
  v7 = (*(v5 + 772))(v4);
  v8 = _vbaObjSet(&v146, v7);
  v9 = (*(*v8 + 160))(v8, &v148);
  __asm { fnclex }
  if ( v9 < 0 )
    _vbaHresultCheckObj(v9, v8, dword_401AA8, 160);
  v10 = _vbaVarMove;
  v134 = (_vbaLenBstr)(v148);
  v133[0] = 3;
  (_vbaVarMove)(v153, v133);
  (_vbaFreeStr)(&v148);
  _vbaFreeObj(&v146, v163);
  v11 = (*(*v4 + 768))(v4);
  v12 = _vbaObjSet(&v146, v11);
  v13 = *v12;
  v128 = v12;
  v14 = (*(v13 + 160))(v12, &v148);
  __asm { fnclex }
  if ( v14 < 0 )
    _vbaHresultCheckObj(v14, v128, dword_401AA8, 160);
  v15 = (_vbaLenBstr)(v148);
  v152 = (_vbaI2I4)(v15);
  (_vbaFreeStr)(&v148);
  _vbaFreeObj(&v146, v163);
  v16 = (*(*v4 + 772))(v4);
  v17 = _vbaObjSet(&v146, v16);
  v18 = *v17;
  v128 = v17;
  v19 = (*(v18 + 160))(v17, &v148);
  __asm { fnclex }
  if ( v19 < 0 )
    _vbaHresultCheckObj(v19, v128, dword_401AA8, 160);
  v20 = v148;
  v148 = 0;
  (_vbaStrMove)(v155, v20);
  _vbaFreeObj(&v146, v163);
  v134 = 6;
  LOWORD(v132) = -(v152 < 6);
  v133[0] = 32770;
  v131[0] = 11;
  v21 = (_vbaVarCmpLt)(v143, v133, v153);
  v22 = (_vbaVarOr)(v141, v131, v21);
  LOWORD(v128) = (_vbaBoolVarNull)(v22);
  (_vbaFreeVar)(v131);
  if ( v128 )
  {
    v138 = -2147352572;
    v137[0] = 10;
    v140 = -2147352572;
    v139[0] = 10;
    v142 = -2147352572;
    v141[0] = 10;
    v134 = L"Please make sure both username and password contain six or more characters.";
    v133[0] = 8;
    (_vbaVarDup)(v143, v133);
    (rtcMsgBox)(v143, 0, v141, v139, v137);
    (_vbaFreeVarList)(4, v143, v141, v139, v137);
    goto LABEL_48;
  }
  v23 = *v4;
  v134 = 1;
  v133[0] = 2;
  v24 = (*(v23 + 772))(v4);
  v25 = _vbaObjSet(&v146, v24);
  v26 = *v25;
  v128 = v25;
  v27 = (*(v26 + 160))(v25, &v148);
  __asm { fnclex }
  if ( v27 < 0 )
    _vbaHresultCheckObj(v27, v128, dword_401AA8, 160);
  v132 = (_vbaLenBstr)(v148);
  v131[0] = 3;
  v130 = 1;
  v129[0] = 2;
  v124 = (_vbaVarForInit)(v158, v126, v125, v129, v131, v133);
  (_vbaFreeStr)(&v148);
  _vbaFreeObj(&v146, v163);
  while ( v124 )
  {
    v30 = (*(*v4 + 772))(v4);
    _vbaObjSet(&v145, v30);
    v31 = (*(*v4 + 796))(v4);
    v32 = _vbaObjSet(&v146, v31);
    v144 = v145;
    v128 = v32;
    v142 = 1;
    v141[0] = 2;
    v145 = 0;
    v143[0] = 9;
    v33 = (_vbaI4Var)(v158, v141);
    (rtcMidCharVar)(v139, v143, v33, v163);                 //get one char of the username
    v34 = *v32;
    v163 = v139;
    v35 = (_vbaStrVarVal)(&v148);
    v36 = v34;
    v37 = v128;
    v38 = (*(v36 + 84))(v128, v35);
    __asm { fnclex }
    if ( v38 < 0 )
      _vbaHresultCheckObj(v38, v37, dword_401B54, 84);
    (_vbaFreeStr)(&v148);
    (_vbaFreeObjList)(2, &v146, &v145);
    (_vbaFreeVarList)(3, v143, v141, v139);
    v39 = (*(*v4 + 792))(v4);
    v40 = _vbaObjSet(&v145, v39);
    v41 = *v4;
    v127 = v40;
    v42 = (*(v41 + 796))(v4);
    v43 = _vbaObjSet(&v146, v42);
    v44 = (*(*v43 + 80))(v43, &v148);
    __asm { fnclex }
    if ( v44 < 0 )
      _vbaHresultCheckObj(v44, v43, dword_401B54, 80);
    v162 = v148;
    v45 = *v127;
    v46 = (rtcAnsiValueBstr)(v148);
    v47 = (_vbaStrI2)(v46);                                 //string to int
    v48 = (_vbaStrMove)(&v147, v47);
    v49 = v45;
    v50 = v127;
    v51 = (*(v49 + 84))(v127, v48);
    __asm { fnclex }
    if ( v51 < 0 )
      _vbaHresultCheckObj(v51, v50, dword_401B54, 84);
    (_vbaFreeStrList)(2, &v148, &v147);
    (_vbaFreeObjList)(2, &v146, &v145);
    v52 = (*(*v4 + 792))(v4);
    v53 = _vbaObjSet(&v146, v52);
    v54 = (*(*v53 + 80))(v53, &v148);
    __asm { fnclex }
    if ( v54 < 0 )
      _vbaHresultCheckObj(v54, v53, dword_401B54, 80);
    v55 = (_vbaR8Str)(v148);                            //string to float
    v123 = v6;
    v122 = v6;
    v57 = v55 + v122;            //accumulating values
    if ( (v56 & 0xD) != 0 )
      goto LABEL_59;
    v6 = (_vbaFpI2)(v57);           //float to int
    (_vbaFreeStr)(&v148);
    _vbaFreeObj(&v146, v163);
    v58 = (_vbaStrBool)(-1);
    (_vbaStrMove)(v155, v58);
    v10 = _vbaVarMove;
    v124 = (_vbaVarForNext)(v158, v126, v125);
  }

//first part
  v59 = 7 * v6;   //v6 is probably accumulated value (sum of ascii values)
  if ( !is_mul_ok(7u, v6) )
    goto LABEL_58;
  v60 = __OFADD__(56, v59);
  v61 = v59 + 56;
  if ( v60 )
    goto LABEL_58;
  v121 = v61;
  v120 = v61;
  v62 = v120;
  if ( dword_404000 )
    (adj_fdiv_m64)(0, 0x40000000);
  else
    v62 = v120 / 2.0;
  if ( (v63 & 0xD) != 0 )
LABEL_59:
    (j___vbaFPException)();
  v67 = (_vbaFpI2)(v163, v164, v62);
  (_vbaStrI2)(v67);
  v10(v150, v143);   //__vbaVarMove
  v144 = 4;
  v143[0] = 2;
  v68 = (_vbaStrVarVal)(&v148, v150, 1, v143); //v68 - our value as string
  v142 = (rtcMidCharBstr)(v68, v161, v162);
  v141[0] = 8;
  v10(v150, v141);
  (_vbaFreeStr)(&v148);
  (_vbaFreeVar)(v143);

//second part
  LOWORD(v28) = 9 * v6;
  if ( !is_mul_ok(9u, v6) || (v60 = __OFADD__(45, v28), LOWORD(v28) = v28 + 45, v60) )
LABEL_58:
    (_vbaErrorOverflow)(v29, v28);
  v119 = v28;
  v118 = v28;
  v69 = v118;
  if ( dword_404000 )
    (adj_fdiv_m64)(0, 0x40000000);
  else
    v69 = v118 / 2.0;
  if ( (v70 & 0xD) != 0 )
    goto LABEL_59;
  v74 = (_vbaFpI2)(v163, v164, v69);
  (_vbaStrI2)(v74);
  v10(v149, v143);
  v144 = 4;
  v143[0] = 2;
  v75 = (_vbaStrVarVal)(&v148, v149, 1, v143);
  v142 = (rtcMidCharBstr)(v75, v161, v162);
  v141[0] = 8;
  v10(v149, v141);
  (_vbaFreeStr)(&v148);
  (_vbaFreeVar)(v143);

//third part
  LOWORD(v29) = 8 * v6;
  if ( !is_mul_ok(8u, v6) )
    goto LABEL_58;
  v60 = __OFADD__(32, v29);
  LOWORD(v29) = v29 + 32;
  if ( v60 )
    goto LABEL_58;
  v117 = v29;
  v116 = v29;
  v76 = v116;
  if ( dword_404000 )
    (adj_fdiv_m64)(0, 0x40000000);
  else
    v76 = v116 / 2.0;
  if ( (v77 & 0xD) != 0 )
    goto LABEL_59;
  v81 = (_vbaFpI2)(v163, v164, v76);
  (_vbaStrI2)(v81);
  v10(v151, v143);
  v144 = 4;
  v143[0] = 2;
  v82 = (_vbaStrVarVal)(&v148, v151, 1, v143);
  v142 = (rtcMidCharBstr)(v82, v161, v162);
  v141[0] = 8;
  v10(v151, v141);
  (_vbaFreeStr)(&v148);
  (_vbaFreeVar)(v143);

//fourth
  v84 = v6;
  v83 = 6 * v6;
  if ( !is_mul_ok(6u, v84) )
    goto LABEL_58;
  v60 = __OFADD__(60, v83);
  v85 = v83 + 60;
  if ( v60 )
    goto LABEL_58;
  v115 = v85;
  v114 = v85;
  v86 = v114;
  if ( dword_404000 )
    (adj_fdiv_m64)(0, 0x40000000);
  else
    v86 = v114 / 2.0;
  if ( (v87 & 0xD) != 0 )
    goto LABEL_59;
  v91 = (_vbaFpI2)(v163, v164, v86);
  (_vbaStrI2)(v91);
  v10(v157, v143);
  v164 = v143;
  v163 = 1;
  v144 = 4;
  v143[0] = 2;
  v92 = (_vbaStrVarVal)(&v148, v157);
  v142 = (rtcMidCharBstr)(v92, v161, v162);
  v141[0] = 8;
  v10(v157, v141);
  (_vbaFreeStr)(&v148);
  (_vbaFreeVar)(v143);
  v134 = dword_401B68;   //dword_401B68 = 0x2D = '-' character
  v132 = dword_401B68;
  v130 = dword_401B68;
  v133[0] = 8;
  v131[0] = 8;
  v129[0] = 8;
  v93 = (_vbaVarAdd)(v143, v133, v150);        //seems like serial concatenating
  v94 = (_vbaVarAdd)(v141, v149, v93);         //seems like serial concatenating
  v95 = (_vbaVarAdd)(v139, v131, v94);         //seems like serial concatenating
  v96 = (_vbaVarAdd)(v137, v151, v95);         //seems like serial concatenating
  v97 = (_vbaVarAdd)(v136, v129, v96);         //seems like serial concatenating
  v98 = (_vbaVarAdd)(v135, v157, v97);         //seems like serial concatenating
  v99 = (_vbaStrVarMove)(v98);
  (_vbaStrMove)(&v156, v99);
  (_vbaFreeVarList)(6, v143, v141, v139, v137, v136, v135);
LABEL_48:
  if ( (_vbaBoolStr)(v155[0]) == 0xFFFF )
  {
    v100 = (*(*v4 + 768))(v4);
    v101 = _vbaObjSet(&v146, v100);
    v102 = *v101;
    v128 = v101;
    v103 = (*(v102 + 160))(v101, &v148);
    __asm { fnclex }
    if ( v103 < 0 )
      _vbaHresultCheckObj(v103, v128, dword_401AA8, 160);
    v127 = -((_vbaStrCmp)(v156, v148) == 0);               //serial comparing
    (_vbaFreeStr)(&v148);
    _vbaFreeObj(&v146, v163);
    v138 = -2147352572;
    v137[0] = 10;
    v140 = -2147352572;
    v139[0] = 10;
    v142 = -2147352572;
    v141[0] = 10;
    if ( v127 )
    {
      v104 = (*(*v4 + 772))(v4);
      v105 = _vbaObjSet(&v146, v104);
      v106 = (*(*v105 + 160))(v105, &v148);
      __asm { fnclex }
      if ( v106 < 0 )
        _vbaHresultCheckObj(v106, v105, dword_401AA8, 160);
      v107 = (_vbaStrCat)(v148, L"Congrats ");
      v108 = (_vbaStrMove)(&v147, v107);
      v144 = (_vbaStrCat)(L", you got your serial right. Now make a keygen for this.", v108);
      v143[0] = 8;
      (rtcMsgBox)(v143, 0, v141, v139, v137);
      (_vbaFreeStrList)(2, &v148, &v147);
      _vbaFreeObj(&v146, v163);
      v162 = v137;
      v161 = v139;
      v160 = v141;
      v159 = v143;
    }
    else
    {
      v134 = L"Sorry, try again.";
      v133[0] = 8;
      (_vbaVarDup)(v143, v133);
      (rtcMsgBox)(v143, 0, v141, v139, v137);
      v162 = v137;
      v161 = v139;
      v160 = v141;
      v159 = v143;
    }
    (_vbaFreeVarList)(4, v159, v160, v161, v162);
    v109 = (_vbaStrBool)(0);
    (_vbaStrMove)(v155, v109);
  }
  v162 = sub_40338A;
  (_vbaFreeVarList)(2, v126, v125);
  (_vbaFreeVar)(v158, v162);
  (_vbaFreeVar)(v157);
  (_vbaFreeStr)(&v156);
  (_vbaFreeStr)(v155);
  (_vbaFreeStr)(&v154);
  (_vbaFreeVar)(v153);
  (_vbaFreeVar)(v151);
  (_vbaFreeVar)(v150);
  return (_vbaFreeVar)(v149);
}
