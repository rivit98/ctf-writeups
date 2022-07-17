from z3 import *
from pwn import *

def sub_19F971(a1):
    return (((((((((((((((((((((((((((((((((((((((a1 - 0x41BF1CD388C76D0C) ^ 0x62E1B3C2289C0687) - 0x529F417EF9778C07) ^ 0x7892A433AE0FBF97)
                                            - 0x624CED65CFB3011) ^ 0xA359D7264A3D6F6F)
                                          + 0x25E0C8F00A91712) ^ 0x6CB5AFB4CDBA1681)
                                        + 0x3A7032F544A3DE38) ^ 0x90567841F20A1BA4)
                                      - 0x2FC7255BF548A0AB) ^ 0xF89B95BF10357A99)
                                    + 0x304F858AE0682EE9) ^ 0x4EE6BC310F2E0255)
                                  - 0x573726BD8443C2B9) ^ 0xDDD256B2989FBA8F)
                                - 0x7DC5DD13787098F9) ^ 0x540F0CDD3127B81F)
                              - 0x2038E70B96CAF92B) ^ 0x9D9B092228C98E3D)
                            - 0x37E28E9CB0868852) ^ 0xC88511E8F60EFE47)
                          + 0x756B98DA70BE94EF) ^ 0x29F01A3DC47DE3E7)
                        + 0x5245D59B5F8BBB15) ^ 0xE294E98008135892)
                      - 0x12896613D92912FF) ^ 0x2249ED0E40149BCC)
                    + 0x1B35898BD2D458B2) ^ 0xDB60CF8F1B423655)
                  + 0x51CCB2E33C2FD323) ^ 0x21B8929306440A39)
                + 0x43A549CF398E8541) ^ 0xE715B1B13DD71D31)
              + 0x4759F809D4A7A773) ^ 0x47189229CE94459B)
            - 0x100D126C36C5E1EB) ^ 0x9236EC65FE3FB63A)
            - 0x23BC9E2215E3C6E4) ^ 0x464643AD06FDC740


def sub_19FC07(a1):
    return (((((((((((((((((((((((((((((((((((((((a1 - 0x30D5C16AC63E9C4F) ^ 0x1660B746FC08A9EC) - 0x5290647CA6099154) ^ 0x4C53A2A291A472CB)
                                            + 0xCD4E18669507479) ^ 0x90E4AC13A7C9F85B)
                                          + 0x4F7D5A8632A5A669) ^ 0x563712392BBD0766)
                                        - 0x71B7DF146C99651C) ^ 0x8CA3617DE699CB02)
                                      - 0x198F2597A73D4745) ^ 0xFD5FB2E3C7DB9F5B)
                                    + 0x3D1EC3286B0930FE) ^ 0x473B9C5DE91A644A)
                                  - 0x4209D24C32FB9E5) ^ 0x7F74AA1B33BDABA7)
                                + 0x7BD17A64472CB382) ^ 0x3CA34BAE15D7CD9B)
                              - 0x4734BD2910617B6A) ^ 0xE6F6C53EFE993B3C)
                            - 0x4BE8948B1AC1AE95) ^ 0xB480C6EA01472BB0)
                          - 0x773CCE2B4F6E8374) ^ 0x2985245CD47DF6E7)
                        - 0x42D78799EC9403CF) ^ 0x12EF928B95B5DA2A)
                      - 0x1BE686A0133070F1) ^ 0x197381241886B8E5)
                    - 0xC554C50A87041B) ^ 0xFE5D0BF999B67107)
                  + 0x21F03E535FBA3063) ^ 0x6DF3B188EBC5132A)
                - 0x515FCD37C8813650) ^ 0x907C2A25D706408E)
              + 0x3E0B5A79497852B6) ^ 0x67B4350403EF7895)
            + 0x2DF0B19DCB3BFC14) ^ 0xE375B15F8D80C945)
            + 0x7E5D0E43A02FC901) ^ 0xDB1B5D62FDC594F


def sub_19FE9D(a1):
    return (((((((((((((((((((((((((((((((((((((((a1 + 0x5D7B919E7B4F2505) ^ 0x1373A63BAA9B4B79) - 0x1CCB359EBF4AFFA0) ^ 0xA80F9AF44B8F05DA)
                                            + 0x11F035A02D6919) ^ 0xDD021659BF4BAEE1)
                                          - 0x418989BA399F5185) ^ 0xE7792D89332F2F79)
                                        - 0x1222B9C9BC41201E) ^ 0x856C182591BB4907)
                                      - 0x32AEAC58C6DBBA05) ^ 0xBDC96D763559FBDA)
                                    + 0x73D29B7C98623E28) ^ 0xD8F00F4AA3E28D55)
                                  + 0x3A73086C2A7C8B6E) ^ 0xF2339D7F3D111FC9)
                                + 0x561D55B57C881BB3) ^ 0x77152798932779A7)
                              - 0x7F38AD2C006C29A4) ^ 0xEE092997A178BAEF)
                            - 0x490795BA4540782C) ^ 0x43BE354E962864B5)
                          + 0x1F82C9B673A83791) ^ 0xBD1A3EBBFB29C411)
                        + 0x2D8D993ED3016E23) ^ 0x6E4DCDAFF0A1775F)
                      - 0x7EB3A42B354CC27F) ^ 0x65A2AA191D956BE)
                    - 0x18188E23237BFB59) ^ 0x806E8075AFC398B7)
                  + 0x7CE44899978432FC) ^ 0xA3F68E3CA0B19A1C)
                + 0x16FCEA72C169D10) ^ 0x8F5FA0EA4F96F137)
              + 0x1EF74DF00CCE00F3) ^ 0xA7551E57E3E57D31)
            + 0x73145DBA10B8A577) ^ 0x6902EEFE25A1C0FB)
            + 0x76B2D6F1B254B3F6) ^ 0x2AFFE6D94C9B2447


def sub_1A0133(a1):
    return (((((((((((((((((((((((((((((((((((((((a1 + 0x10582E08F795C2E4) ^ 0xF317DAAF6688745) + 0x3E25CF4A5F82AF04) ^ 0xEE6215CF96D0F074)
                                            + 0xB659873EFE594B7) ^ 0xDDF3BAA4890A805D)
                                          - 0x37509D043ABA55AD) ^ 0x16B04054F4D5529F)
                                        + 0x65F79A5706818D94) ^ 0x811BD4050F5EE4CB)
                                      - 0x5DA97EF5ACA38703) ^ 0x6EA711943CA7E6A8)
                                    - 0x6936EE4E6DB58CB1) ^ 0x1AEDB7BB82569424)
                                  - 0x45459FE5007907D4) ^ 0xDA301E57443F0CCA)
                                - 0x6928334EE11E5DD9) ^ 0xA6704DB08044A88D)
                              - 0x6ECBE44FFC916190) ^ 0x6788423E1ED0475B)
                            - 0x28F91830E5718E40) ^ 0xCE6278422A4DC5C2)
                          - 0x493016A4FCB18CF2) ^ 0x7C973285AC7E958B)
                        - 0x2F5F4C12559EDA96) ^ 0xC2B7AE98C6AAE026)
                      + 0x1C3C4FC2A8C3E3AC) ^ 0x2D487C098812B602)
                    - 0x34598C3B84C447D8) ^ 0x1BEEAA537B4AE5EE)
                  - 0x6E5F4EC5CE0645B0) ^ 0x1A7381A0CD322F0E)
                - 0x54178D8119561CD2) ^ 0x32B71BC26BA1B408)
              - 0x4ACD088E6F5514A) ^ 0x5BE8A9369286AB6)
            + 0x7FABF8B40DEA85FD) ^ 0x1FB1DA2A058A9325)
            + 0x174C77DEE25DD880) ^ 0xE5E7EB215A9967E4


def sub_1A03C9(a1):
    return (((((((((((((((((((((((((((((((((((((((a1 + 0x31F08BA5E8ECC934) ^ 0x3861A351EE034627) - 0x2622900CF3581992) ^ 0xC92D83F6F548609)
                                      + 0x6D5A9AB496003EA9) ^ 0x3DB758F5F95D7699)
                                    - 0x57FD2D8B2751427E) ^ 0x4F355438B0429FD3)
                                  - 0x168A5B38F96914ED) ^ 0x3B1AB46D3189A414)
                                + 0x24BAC5228BAA669B) ^ 0x7A0C772F57F0DC69)
                              - 0xD9B8A0B6FD8CAC6) ^ 0x9560E2C37BBF308C)
                            - 0xD4614007F076B8D) ^ 0x5E5541800B7DEBEA)
                          + 0x5F9F537BD20D2D35) ^ 0x3B3E2C30A845C482)
                        - 0x3BD3DAD274CF9A6F) ^ 0x4964664E9BD064F)
                      - 0x622DE3BB8B347D34) ^ 0xF7228C44D58887DE)
                    + 0x5CF5FC9CF96A4E85) ^ 0x21E700BB552789B2)
                  + 0x223C3BD86CE929F7) ^ 0xB8B404CC2F3692BC)
                - 0x1304A86DB1D31C59) ^ 0x6576FC1EAD907C1D)
              - 0x49FD72856E437A2D) ^ 0x916EBA22621696D1)
            - 0x7812D06C9C31B984) ^ 0x8C7B02888BF0591E)
                  + 0x5B041E8E25EB245F) ^ 0x2ECE8CE04CB3AC56)
                - 0x3FF6DC3A2E2D9CB9) ^ 0xA65D41781C9FA46D)
              + 0x192C7A321A30CBA6) ^ 0xB09A06B01E19DB02)
            - 0x4816B06D67BE2F00) ^ 0xF07E5C46E440FEC7


t = [ 0xF161495256A9BE7E,
    0x9ED1F35982D3567D,
     0x5E8932B407B62517,
     0x5B65919C50A3B933,
     0x5F27B58FA8883409,]

efs = [sub_19F971, sub_19FC07, sub_19FE9D, sub_1A0133, sub_1A03C9]

parts = []
for t, e in zip(t, efs):
	v = BitVec('x', 64)

	s = Solver()
	s.add(e(v) == t)
	if s.check() == sat:
		parts.append(unhex(hex(s.model()[v].as_long())[2:])[::-1])
	else:
		print("unsat")

print(parts)
print(b''.join(parts))
