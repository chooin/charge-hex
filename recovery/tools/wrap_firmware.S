.syntax unified
.cpu cortex-m0
.thumb
.section .text,"ax",%progbits
.global firmware_base
firmware_base:
.incbin "recovery/artifacts/firmware.preliminary.bin", 0, 180
.global fn_080000b4
.type fn_080000b4,%function
.thumb_func
fn_080000b4:
.incbin "recovery/artifacts/firmware.preliminary.bin", 180, 8
.global fn_080000bc
.type fn_080000bc,%function
.thumb_func
fn_080000bc:
.incbin "recovery/artifacts/firmware.preliminary.bin", 188, 12
.global Reset_Handler
.type Reset_Handler,%function
.thumb_func
Reset_Handler:
.incbin "recovery/artifacts/firmware.preliminary.bin", 200, 18
.global fn_080000da
.type fn_080000da,%function
.thumb_func
fn_080000da:
.incbin "recovery/artifacts/firmware.preliminary.bin", 218, 10
.global fn_080000e4
.type fn_080000e4,%function
.thumb_func
fn_080000e4:
.incbin "recovery/artifacts/firmware.preliminary.bin", 228, 44
.global fn_08000110
.type fn_08000110,%function
.thumb_func
fn_08000110:
.incbin "recovery/artifacts/firmware.preliminary.bin", 272, 96
.global fn_08000170
.type fn_08000170,%function
.thumb_func
fn_08000170:
.incbin "recovery/artifacts/firmware.preliminary.bin", 368, 34
.global fn_08000192
.type fn_08000192,%function
.thumb_func
fn_08000192:
.incbin "recovery/artifacts/firmware.preliminary.bin", 402, 14
.global fn_080001a0
.type fn_080001a0,%function
.thumb_func
fn_080001a0:
.incbin "recovery/artifacts/firmware.preliminary.bin", 416, 22
.global fn_080001b6
.type fn_080001b6,%function
.thumb_func
fn_080001b6:
.incbin "recovery/artifacts/firmware.preliminary.bin", 438, 34
.global fn_080001d8
.type fn_080001d8,%function
.thumb_func
fn_080001d8:
.incbin "recovery/artifacts/firmware.preliminary.bin", 472, 36
.global fn_080001fc
.type fn_080001fc,%function
.thumb_func
fn_080001fc:
.incbin "recovery/artifacts/firmware.preliminary.bin", 508, 36
.global fn_08000220
.type fn_08000220,%function
.thumb_func
fn_08000220:
.incbin "recovery/artifacts/firmware.preliminary.bin", 544, 16
.global fn_08000230
.type fn_08000230,%function
.thumb_func
fn_08000230:
.incbin "recovery/artifacts/firmware.preliminary.bin", 560, 36
.global fn_08000254
.type fn_08000254,%function
.thumb_func
fn_08000254:
.incbin "recovery/artifacts/firmware.preliminary.bin", 596, 40
.global fn_0800027c
.type fn_0800027c,%function
.thumb_func
fn_0800027c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 636, 4
.global fn_08000280
.type fn_08000280,%function
.thumb_func
fn_08000280:
.incbin "recovery/artifacts/firmware.preliminary.bin", 640, 128
.global fn_08000300
.type fn_08000300,%function
.thumb_func
fn_08000300:
.incbin "recovery/artifacts/firmware.preliminary.bin", 768, 32
.global fn_08000320
.type fn_08000320,%function
.thumb_func
fn_08000320:
.incbin "recovery/artifacts/firmware.preliminary.bin", 800, 36
.global fn_08000344
.type fn_08000344,%function
.thumb_func
fn_08000344:
.incbin "recovery/artifacts/firmware.preliminary.bin", 836, 36
.global fn_08000368
.type fn_08000368,%function
.thumb_func
fn_08000368:
.incbin "recovery/artifacts/firmware.preliminary.bin", 872, 32
.global fn_08000388
.type fn_08000388,%function
.thumb_func
fn_08000388:
.incbin "recovery/artifacts/firmware.preliminary.bin", 904, 24
.global fn_080003a0
.type fn_080003a0,%function
.thumb_func
fn_080003a0:
.incbin "recovery/artifacts/firmware.preliminary.bin", 928, 4
.global fn_080003a4
.type fn_080003a4,%function
.thumb_func
fn_080003a4:
.incbin "recovery/artifacts/firmware.preliminary.bin", 932, 56
.global fn_080003dc
.type fn_080003dc,%function
.thumb_func
fn_080003dc:
.incbin "recovery/artifacts/firmware.preliminary.bin", 988, 80
.global fn_0800042c
.type fn_0800042c,%function
.thumb_func
fn_0800042c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 1068, 128
.global fn_080004ac
.type fn_080004ac,%function
.thumb_func
fn_080004ac:
.incbin "recovery/artifacts/firmware.preliminary.bin", 1196, 64
.global fn_080004ec
.type fn_080004ec,%function
.thumb_func
fn_080004ec:
.incbin "recovery/artifacts/firmware.preliminary.bin", 1260, 72
.global fn_08000534
.type fn_08000534,%function
.thumb_func
fn_08000534:
.incbin "recovery/artifacts/firmware.preliminary.bin", 1332, 74
.global fn_0800057e
.type fn_0800057e,%function
.thumb_func
fn_0800057e:
.incbin "recovery/artifacts/firmware.preliminary.bin", 1406, 4
.global fn_08000582
.type fn_08000582,%function
.thumb_func
fn_08000582:
.incbin "recovery/artifacts/firmware.preliminary.bin", 1410, 158
.global fn_08000620
.type fn_08000620,%function
.thumb_func
fn_08000620:
.incbin "recovery/artifacts/firmware.preliminary.bin", 1568, 84
.global fn_08000674
.type fn_08000674,%function
.thumb_func
fn_08000674:
.incbin "recovery/artifacts/firmware.preliminary.bin", 1652, 108
.global fn_080006e0
.type fn_080006e0,%function
.thumb_func
fn_080006e0:
.incbin "recovery/artifacts/firmware.preliminary.bin", 1760, 160
.global fn_08000780
.type fn_08000780,%function
.thumb_func
fn_08000780:
.incbin "recovery/artifacts/firmware.preliminary.bin", 1920, 20
.global fn_08000794
.type fn_08000794,%function
.thumb_func
fn_08000794:
.incbin "recovery/artifacts/firmware.preliminary.bin", 1940, 124
.global fn_08000810
.type fn_08000810,%function
.thumb_func
fn_08000810:
.incbin "recovery/artifacts/firmware.preliminary.bin", 2064, 40
.global fn_08000838
.type fn_08000838,%function
.thumb_func
fn_08000838:
.incbin "recovery/artifacts/firmware.preliminary.bin", 2104, 212
.global fn_0800090c
.type fn_0800090c,%function
.thumb_func
fn_0800090c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 2316, 368
.global fn_08000a7c
.type fn_08000a7c,%function
.thumb_func
fn_08000a7c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 2684, 12
.global fn_08000a88
.type fn_08000a88,%function
.thumb_func
fn_08000a88:
.incbin "recovery/artifacts/firmware.preliminary.bin", 2696, 12
.global fn_08000a94
.type fn_08000a94,%function
.thumb_func
fn_08000a94:
.incbin "recovery/artifacts/firmware.preliminary.bin", 2708, 74
.global fn_08000ade
.type fn_08000ade,%function
.thumb_func
fn_08000ade:
.incbin "recovery/artifacts/firmware.preliminary.bin", 2782, 74
.global fn_08000b28
.type fn_08000b28,%function
.thumb_func
fn_08000b28:
.incbin "recovery/artifacts/firmware.preliminary.bin", 2856, 180
.global fn_08000bdc
.type fn_08000bdc,%function
.thumb_func
fn_08000bdc:
.incbin "recovery/artifacts/firmware.preliminary.bin", 3036, 272
.global fn_08000cec
.type fn_08000cec,%function
.thumb_func
fn_08000cec:
.incbin "recovery/artifacts/firmware.preliminary.bin", 3308, 340
.global fn_08000e40
.type fn_08000e40,%function
.thumb_func
fn_08000e40:
.incbin "recovery/artifacts/firmware.preliminary.bin", 3648, 332
.global fn_08000f8c
.type fn_08000f8c,%function
.thumb_func
fn_08000f8c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 3980, 56
.global fn_08000fc4
.type fn_08000fc4,%function
.thumb_func
fn_08000fc4:
.incbin "recovery/artifacts/firmware.preliminary.bin", 4036, 100
.global fn_08001028
.type fn_08001028,%function
.thumb_func
fn_08001028:
.incbin "recovery/artifacts/firmware.preliminary.bin", 4136, 16
.global fn_08001038
.type fn_08001038,%function
.thumb_func
fn_08001038:
.incbin "recovery/artifacts/firmware.preliminary.bin", 4152, 32
.global fn_08001058
.type fn_08001058,%function
.thumb_func
fn_08001058:
.incbin "recovery/artifacts/firmware.preliminary.bin", 4184, 68
.global fn_0800109c
.type fn_0800109c,%function
.thumb_func
fn_0800109c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 4252, 40
.global fn_080010c4
.type fn_080010c4,%function
.thumb_func
fn_080010c4:
.incbin "recovery/artifacts/firmware.preliminary.bin", 4292, 32
.global fn_080010e4
.type fn_080010e4,%function
.thumb_func
fn_080010e4:
.incbin "recovery/artifacts/firmware.preliminary.bin", 4324, 24
.global fn_080010fc
.type fn_080010fc,%function
.thumb_func
fn_080010fc:
.incbin "recovery/artifacts/firmware.preliminary.bin", 4348, 8
.global fn_08001104
.type fn_08001104,%function
.thumb_func
fn_08001104:
.incbin "recovery/artifacts/firmware.preliminary.bin", 4356, 232
.global fn_080011ec
.type fn_080011ec,%function
.thumb_func
fn_080011ec:
.incbin "recovery/artifacts/firmware.preliminary.bin", 4588, 264
.global fn_080012f4
.type fn_080012f4,%function
.thumb_func
fn_080012f4:
.incbin "recovery/artifacts/firmware.preliminary.bin", 4852, 32
.global fn_08001314
.type fn_08001314,%function
.thumb_func
fn_08001314:
.incbin "recovery/artifacts/firmware.preliminary.bin", 4884, 128
.global fn_08001394
.type fn_08001394,%function
.thumb_func
fn_08001394:
.incbin "recovery/artifacts/firmware.preliminary.bin", 5012, 904
.global fn_0800171c
.type fn_0800171c,%function
.thumb_func
fn_0800171c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 5916, 48
.global fn_0800174c
.type fn_0800174c,%function
.thumb_func
fn_0800174c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 5964, 16
.global fn_0800175c
.type fn_0800175c,%function
.thumb_func
fn_0800175c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 5980, 96
.global fn_080017bc
.type fn_080017bc,%function
.thumb_func
fn_080017bc:
.incbin "recovery/artifacts/firmware.preliminary.bin", 6076, 36
.global fn_080017e0
.type fn_080017e0,%function
.thumb_func
fn_080017e0:
.incbin "recovery/artifacts/firmware.preliminary.bin", 6112, 128
.global fn_08001860
.type fn_08001860,%function
.thumb_func
fn_08001860:
.incbin "recovery/artifacts/firmware.preliminary.bin", 6240, 4
.global fn_08001864
.type fn_08001864,%function
.thumb_func
fn_08001864:
.incbin "recovery/artifacts/firmware.preliminary.bin", 6244, 520
.global fn_08001a6c
.type fn_08001a6c,%function
.thumb_func
fn_08001a6c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 6764, 108
.global fn_08001ad8
.type fn_08001ad8,%function
.thumb_func
fn_08001ad8:
.incbin "recovery/artifacts/firmware.preliminary.bin", 6872, 60
.global fn_08001b14
.type fn_08001b14,%function
.thumb_func
fn_08001b14:
.incbin "recovery/artifacts/firmware.preliminary.bin", 6932, 164
.global fn_08001bb8
.type fn_08001bb8,%function
.thumb_func
fn_08001bb8:
.incbin "recovery/artifacts/firmware.preliminary.bin", 7096, 252
.global fn_08001cb4
.type fn_08001cb4,%function
.thumb_func
fn_08001cb4:
.incbin "recovery/artifacts/firmware.preliminary.bin", 7348, 2
.global fn_08001cb6
.type fn_08001cb6,%function
.thumb_func
fn_08001cb6:
.incbin "recovery/artifacts/firmware.preliminary.bin", 7350, 2
.global fn_08001cb8
.type fn_08001cb8,%function
.thumb_func
fn_08001cb8:
.incbin "recovery/artifacts/firmware.preliminary.bin", 7352, 210
.global fn_08001d8a
.type fn_08001d8a,%function
.thumb_func
fn_08001d8a:
.incbin "recovery/artifacts/firmware.preliminary.bin", 7562, 2
.global fn_08001d8c
.type fn_08001d8c,%function
.thumb_func
fn_08001d8c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 7564, 4
.global fn_08001d90
.type fn_08001d90,%function
.thumb_func
fn_08001d90:
.incbin "recovery/artifacts/firmware.preliminary.bin", 7568, 44
.global fn_08001dbc
.type fn_08001dbc,%function
.thumb_func
fn_08001dbc:
.incbin "recovery/artifacts/firmware.preliminary.bin", 7612, 52
.global fn_08001df0
.type fn_08001df0,%function
.thumb_func
fn_08001df0:
.incbin "recovery/artifacts/firmware.preliminary.bin", 7664, 220
.global fn_08001ecc
.type fn_08001ecc,%function
.thumb_func
fn_08001ecc:
.incbin "recovery/artifacts/firmware.preliminary.bin", 7884, 36
.global fn_08001ef0
.type fn_08001ef0,%function
.thumb_func
fn_08001ef0:
.incbin "recovery/artifacts/firmware.preliminary.bin", 7920, 112
.global fn_08001f60
.type fn_08001f60,%function
.thumb_func
fn_08001f60:
.incbin "recovery/artifacts/firmware.preliminary.bin", 8032, 96
.global fn_08001fc0
.type fn_08001fc0,%function
.thumb_func
fn_08001fc0:
.incbin "recovery/artifacts/firmware.preliminary.bin", 8128, 96
.global fn_08002020
.type fn_08002020,%function
.thumb_func
fn_08002020:
.incbin "recovery/artifacts/firmware.preliminary.bin", 8224, 40
.global fn_08002048
.type fn_08002048,%function
.thumb_func
fn_08002048:
.incbin "recovery/artifacts/firmware.preliminary.bin", 8264, 78
.global fn_08002096
.type fn_08002096,%function
.thumb_func
fn_08002096:
.incbin "recovery/artifacts/firmware.preliminary.bin", 8342, 76
.global fn_080020e2
.type fn_080020e2,%function
.thumb_func
fn_080020e2:
.incbin "recovery/artifacts/firmware.preliminary.bin", 8418, 82
.global fn_08002134
.type fn_08002134,%function
.thumb_func
fn_08002134:
.incbin "recovery/artifacts/firmware.preliminary.bin", 8500, 40
.global fn_0800215c
.type fn_0800215c,%function
.thumb_func
fn_0800215c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 8540, 88
.global fn_080021b4
.type fn_080021b4,%function
.thumb_func
fn_080021b4:
.incbin "recovery/artifacts/firmware.preliminary.bin", 8628, 88
.global fn_0800220c
.type fn_0800220c,%function
.thumb_func
fn_0800220c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 8716, 64
.global fn_0800224c
.type fn_0800224c,%function
.thumb_func
fn_0800224c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 8780, 2
.global fn_0800224e
.type fn_0800224e,%function
.thumb_func
fn_0800224e:
.incbin "recovery/artifacts/firmware.preliminary.bin", 8782, 2
.global fn_08002250
.type fn_08002250,%function
.thumb_func
fn_08002250:
.incbin "recovery/artifacts/firmware.preliminary.bin", 8784, 192
.global fn_08002310
.type fn_08002310,%function
.thumb_func
fn_08002310:
.incbin "recovery/artifacts/firmware.preliminary.bin", 8976, 4
.global fn_08002314
.type fn_08002314,%function
.thumb_func
fn_08002314:
.incbin "recovery/artifacts/firmware.preliminary.bin", 8980, 308
.global fn_08002448
.type fn_08002448,%function
.thumb_func
fn_08002448:
.incbin "recovery/artifacts/firmware.preliminary.bin", 9288, 20
.global fn_0800245c
.type fn_0800245c,%function
.thumb_func
fn_0800245c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 9308, 56
.global fn_08002494
.type fn_08002494,%function
.thumb_func
fn_08002494:
.incbin "recovery/artifacts/firmware.preliminary.bin", 9364, 48
.global fn_080024c4
.type fn_080024c4,%function
.thumb_func
fn_080024c4:
.incbin "recovery/artifacts/firmware.preliminary.bin", 9412, 120
.global fn_0800253c
.type fn_0800253c,%function
.thumb_func
fn_0800253c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 9532, 204
.global fn_08002608
.type fn_08002608,%function
.thumb_func
fn_08002608:
.incbin "recovery/artifacts/firmware.preliminary.bin", 9736, 316
.global fn_08002744
.type fn_08002744,%function
.thumb_func
fn_08002744:
.incbin "recovery/artifacts/firmware.preliminary.bin", 10052, 50
.global fn_08002776
.type fn_08002776,%function
.thumb_func
fn_08002776:
.incbin "recovery/artifacts/firmware.preliminary.bin", 10102, 18
.global fn_08002788
.type fn_08002788,%function
.thumb_func
fn_08002788:
.incbin "recovery/artifacts/firmware.preliminary.bin", 10120, 308
.global fn_080028bc
.type fn_080028bc,%function
.thumb_func
fn_080028bc:
.incbin "recovery/artifacts/firmware.preliminary.bin", 10428, 140
.global fn_08002948
.type fn_08002948,%function
.thumb_func
fn_08002948:
.incbin "recovery/artifacts/firmware.preliminary.bin", 10568, 160
.global fn_080029e8
.type fn_080029e8,%function
.thumb_func
fn_080029e8:
.incbin "recovery/artifacts/firmware.preliminary.bin", 10728, 16
.global fn_080029f8
.type fn_080029f8,%function
.thumb_func
fn_080029f8:
.incbin "recovery/artifacts/firmware.preliminary.bin", 10744, 112
.global fn_08002a68
.type fn_08002a68,%function
.thumb_func
fn_08002a68:
.incbin "recovery/artifacts/firmware.preliminary.bin", 10856, 92
.global fn_08002ac4
.type fn_08002ac4,%function
.thumb_func
fn_08002ac4:
.incbin "recovery/artifacts/firmware.preliminary.bin", 10948, 36
.global fn_08002ae8
.type fn_08002ae8,%function
.thumb_func
fn_08002ae8:
.incbin "recovery/artifacts/firmware.preliminary.bin", 10984, 376
.global fn_08002c60
.type fn_08002c60,%function
.thumb_func
fn_08002c60:
.incbin "recovery/artifacts/firmware.preliminary.bin", 11360, 48
.global fn_08002c90
.type fn_08002c90,%function
.thumb_func
fn_08002c90:
.incbin "recovery/artifacts/firmware.preliminary.bin", 11408, 100
.global boot_main
.type boot_main,%function
.thumb_func
boot_main:
.incbin "recovery/artifacts/firmware.preliminary.bin", 11508, 396
.global fn_08002e80
.type fn_08002e80,%function
.thumb_func
fn_08002e80:
.incbin "recovery/artifacts/firmware.preliminary.bin", 11904, 22
.global fn_08002e96
.type fn_08002e96,%function
.thumb_func
fn_08002e96:
.incbin "recovery/artifacts/firmware.preliminary.bin", 11926, 22
.global fn_08002eac
.type fn_08002eac,%function
.thumb_func
fn_08002eac:
.incbin "recovery/artifacts/firmware.preliminary.bin", 11948, 4616
.global fn_080040b4
.type fn_080040b4,%function
.thumb_func
fn_080040b4:
.incbin "recovery/artifacts/firmware.preliminary.bin", 16564, 8
.global fn_080040bc
.type fn_080040bc,%function
.thumb_func
fn_080040bc:
.incbin "recovery/artifacts/firmware.preliminary.bin", 16572, 16
.global App_Reset_Handler
.type App_Reset_Handler,%function
.thumb_func
App_Reset_Handler:
.incbin "recovery/artifacts/firmware.preliminary.bin", 16588, 18
.global fn_080040de
.type fn_080040de,%function
.thumb_func
fn_080040de:
.incbin "recovery/artifacts/firmware.preliminary.bin", 16606, 10
.global fn_080040e8
.type fn_080040e8,%function
.thumb_func
fn_080040e8:
.incbin "recovery/artifacts/firmware.preliminary.bin", 16616, 44
.global fn_08004114
.type fn_08004114,%function
.thumb_func
fn_08004114:
.incbin "recovery/artifacts/firmware.preliminary.bin", 16660, 40
.global fn_0800413c
.type fn_0800413c,%function
.thumb_func
fn_0800413c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 16700, 96
.global fn_0800419c
.type fn_0800419c,%function
.thumb_func
fn_0800419c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 16796, 34
.global fn_080041be
.type fn_080041be,%function
.thumb_func
fn_080041be:
.incbin "recovery/artifacts/firmware.preliminary.bin", 16830, 14
.global fn_080041cc
.type fn_080041cc,%function
.thumb_func
fn_080041cc:
.incbin "recovery/artifacts/firmware.preliminary.bin", 16844, 22
.global fn_080041e2
.type fn_080041e2,%function
.thumb_func
fn_080041e2:
.incbin "recovery/artifacts/firmware.preliminary.bin", 16866, 122
.global fn_0800425c
.type fn_0800425c,%function
.thumb_func
fn_0800425c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 16988, 124
.global fn_080042d8
.type fn_080042d8,%function
.thumb_func
fn_080042d8:
.incbin "recovery/artifacts/firmware.preliminary.bin", 17112, 44
.global fn_08004304
.type fn_08004304,%function
.thumb_func
fn_08004304:
.incbin "recovery/artifacts/firmware.preliminary.bin", 17156, 16
.global fn_08004314
.type fn_08004314,%function
.thumb_func
fn_08004314:
.incbin "recovery/artifacts/firmware.preliminary.bin", 17172, 40
.global fn_0800433c
.type fn_0800433c,%function
.thumb_func
fn_0800433c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 17212, 50
.global fn_0800436e
.type fn_0800436e,%function
.thumb_func
fn_0800436e:
.incbin "recovery/artifacts/firmware.preliminary.bin", 17262, 40
.global fn_08004396
.type fn_08004396,%function
.thumb_func
fn_08004396:
.incbin "recovery/artifacts/firmware.preliminary.bin", 17302, 56
.global fn_080043ce
.type fn_080043ce,%function
.thumb_func
fn_080043ce:
.incbin "recovery/artifacts/firmware.preliminary.bin", 17358, 32
.global fn_080043ee
.type fn_080043ee,%function
.thumb_func
fn_080043ee:
.incbin "recovery/artifacts/firmware.preliminary.bin", 17390, 16
.global fn_080043fe
.type fn_080043fe,%function
.thumb_func
fn_080043fe:
.incbin "recovery/artifacts/firmware.preliminary.bin", 17406, 114
.global fn_08004470
.type fn_08004470,%function
.thumb_func
fn_08004470:
.incbin "recovery/artifacts/firmware.preliminary.bin", 17520, 26
.global fn_0800448a
.type fn_0800448a,%function
.thumb_func
fn_0800448a:
.incbin "recovery/artifacts/firmware.preliminary.bin", 17546, 166
.global fn_08004530
.type fn_08004530,%function
.thumb_func
fn_08004530:
.incbin "recovery/artifacts/firmware.preliminary.bin", 17712, 36
.global fn_08004554
.type fn_08004554,%function
.thumb_func
fn_08004554:
.incbin "recovery/artifacts/firmware.preliminary.bin", 17748, 132
.global fn_080045d8
.type fn_080045d8,%function
.thumb_func
fn_080045d8:
.incbin "recovery/artifacts/firmware.preliminary.bin", 17880, 40
.global fn_08004600
.type fn_08004600,%function
.thumb_func
fn_08004600:
.incbin "recovery/artifacts/firmware.preliminary.bin", 17920, 10
.global fn_0800460a
.type fn_0800460a,%function
.thumb_func
fn_0800460a:
.incbin "recovery/artifacts/firmware.preliminary.bin", 17930, 34
.global fn_0800462c
.type fn_0800462c,%function
.thumb_func
fn_0800462c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 17964, 36
.global fn_08004650
.type fn_08004650,%function
.thumb_func
fn_08004650:
.incbin "recovery/artifacts/firmware.preliminary.bin", 18000, 388
.global fn_080047d4
.type fn_080047d4,%function
.thumb_func
fn_080047d4:
.incbin "recovery/artifacts/firmware.preliminary.bin", 18388, 332
.global fn_08004920
.type fn_08004920,%function
.thumb_func
fn_08004920:
.incbin "recovery/artifacts/firmware.preliminary.bin", 18720, 32
.global fn_08004940
.type fn_08004940,%function
.thumb_func
fn_08004940:
.incbin "recovery/artifacts/firmware.preliminary.bin", 18752, 32
.global fn_08004960
.type fn_08004960,%function
.thumb_func
fn_08004960:
.incbin "recovery/artifacts/firmware.preliminary.bin", 18784, 32
.global fn_08004980
.type fn_08004980,%function
.thumb_func
fn_08004980:
.incbin "recovery/artifacts/firmware.preliminary.bin", 18816, 296
.global fn_08004aa8
.type fn_08004aa8,%function
.thumb_func
fn_08004aa8:
.incbin "recovery/artifacts/firmware.preliminary.bin", 19112, 76
.global fn_08004af4
.type fn_08004af4,%function
.thumb_func
fn_08004af4:
.incbin "recovery/artifacts/firmware.preliminary.bin", 19188, 28
.global fn_08004b10
.type fn_08004b10,%function
.thumb_func
fn_08004b10:
.incbin "recovery/artifacts/firmware.preliminary.bin", 19216, 700
.global fn_08004dcc
.type fn_08004dcc,%function
.thumb_func
fn_08004dcc:
.incbin "recovery/artifacts/firmware.preliminary.bin", 19916, 552
.global fn_08004ff4
.type fn_08004ff4,%function
.thumb_func
fn_08004ff4:
.incbin "recovery/artifacts/firmware.preliminary.bin", 20468, 24
.global fn_0800500c
.type fn_0800500c,%function
.thumb_func
fn_0800500c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 20492, 24
.global fn_08005024
.type fn_08005024,%function
.thumb_func
fn_08005024:
.incbin "recovery/artifacts/firmware.preliminary.bin", 20516, 36
.global fn_08005048
.type fn_08005048,%function
.thumb_func
fn_08005048:
.incbin "recovery/artifacts/firmware.preliminary.bin", 20552, 40
.global fn_08005070
.type fn_08005070,%function
.thumb_func
fn_08005070:
.incbin "recovery/artifacts/firmware.preliminary.bin", 20592, 88
.global fn_080050c8
.type fn_080050c8,%function
.thumb_func
fn_080050c8:
.incbin "recovery/artifacts/firmware.preliminary.bin", 20680, 68
.global fn_0800510c
.type fn_0800510c,%function
.thumb_func
fn_0800510c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 20748, 68
.global fn_08005150
.type fn_08005150,%function
.thumb_func
fn_08005150:
.incbin "recovery/artifacts/firmware.preliminary.bin", 20816, 28
.global fn_0800516c
.type fn_0800516c,%function
.thumb_func
fn_0800516c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 20844, 48
.global fn_0800519c
.type fn_0800519c,%function
.thumb_func
fn_0800519c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 20892, 20
.global fn_080051b0
.type fn_080051b0,%function
.thumb_func
fn_080051b0:
.incbin "recovery/artifacts/firmware.preliminary.bin", 20912, 96
.global fn_08005210
.type fn_08005210,%function
.thumb_func
fn_08005210:
.incbin "recovery/artifacts/firmware.preliminary.bin", 21008, 128
.global fn_08005290
.type fn_08005290,%function
.thumb_func
fn_08005290:
.incbin "recovery/artifacts/firmware.preliminary.bin", 21136, 12
.global fn_0800529c
.type fn_0800529c,%function
.thumb_func
fn_0800529c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 21148, 4
.global fn_080052a0
.type fn_080052a0,%function
.thumb_func
fn_080052a0:
.incbin "recovery/artifacts/firmware.preliminary.bin", 21152, 32
.global fn_080052c0
.type fn_080052c0,%function
.thumb_func
fn_080052c0:
.incbin "recovery/artifacts/firmware.preliminary.bin", 21184, 36
.global fn_080052e4
.type fn_080052e4,%function
.thumb_func
fn_080052e4:
.incbin "recovery/artifacts/firmware.preliminary.bin", 21220, 36
.global fn_08005308
.type fn_08005308,%function
.thumb_func
fn_08005308:
.incbin "recovery/artifacts/firmware.preliminary.bin", 21256, 32
.global fn_08005328
.type fn_08005328,%function
.thumb_func
fn_08005328:
.incbin "recovery/artifacts/firmware.preliminary.bin", 21288, 24
.global fn_08005340
.type fn_08005340,%function
.thumb_func
fn_08005340:
.incbin "recovery/artifacts/firmware.preliminary.bin", 21312, 4
.global fn_08005344
.type fn_08005344,%function
.thumb_func
fn_08005344:
.incbin "recovery/artifacts/firmware.preliminary.bin", 21316, 4
.global fn_08005348
.type fn_08005348,%function
.thumb_func
fn_08005348:
.incbin "recovery/artifacts/firmware.preliminary.bin", 21320, 56
.global fn_08005380
.type fn_08005380,%function
.thumb_func
fn_08005380:
.incbin "recovery/artifacts/firmware.preliminary.bin", 21376, 80
.global fn_080053d0
.type fn_080053d0,%function
.thumb_func
fn_080053d0:
.incbin "recovery/artifacts/firmware.preliminary.bin", 21456, 128
.global fn_08005450
.type fn_08005450,%function
.thumb_func
fn_08005450:
.incbin "recovery/artifacts/firmware.preliminary.bin", 21584, 176
.global fn_08005500
.type fn_08005500,%function
.thumb_func
fn_08005500:
.incbin "recovery/artifacts/firmware.preliminary.bin", 21760, 272
.global fn_08005610
.type fn_08005610,%function
.thumb_func
fn_08005610:
.incbin "recovery/artifacts/firmware.preliminary.bin", 22032, 8
.global fn_08005618
.type fn_08005618,%function
.thumb_func
fn_08005618:
.incbin "recovery/artifacts/firmware.preliminary.bin", 22040, 376
.global fn_08005790
.type fn_08005790,%function
.thumb_func
fn_08005790:
.incbin "recovery/artifacts/firmware.preliminary.bin", 22416, 88
.global fn_080057e8
.type fn_080057e8,%function
.thumb_func
fn_080057e8:
.incbin "recovery/artifacts/firmware.preliminary.bin", 22504, 92
.global fn_08005844
.type fn_08005844,%function
.thumb_func
fn_08005844:
.incbin "recovery/artifacts/firmware.preliminary.bin", 22596, 64
.global fn_08005884
.type fn_08005884,%function
.thumb_func
fn_08005884:
.incbin "recovery/artifacts/firmware.preliminary.bin", 22660, 72
.global fn_080058cc
.type fn_080058cc,%function
.thumb_func
fn_080058cc:
.incbin "recovery/artifacts/firmware.preliminary.bin", 22732, 156
.global fn_08005968
.type fn_08005968,%function
.thumb_func
fn_08005968:
.incbin "recovery/artifacts/firmware.preliminary.bin", 22888, 84
.global fn_080059bc
.type fn_080059bc,%function
.thumb_func
fn_080059bc:
.incbin "recovery/artifacts/firmware.preliminary.bin", 22972, 108
.global fn_08005a28
.type fn_08005a28,%function
.thumb_func
fn_08005a28:
.incbin "recovery/artifacts/firmware.preliminary.bin", 23080, 36
.global fn_08005a4c
.type fn_08005a4c,%function
.thumb_func
fn_08005a4c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 23116, 160
.global fn_08005aec
.type fn_08005aec,%function
.thumb_func
fn_08005aec:
.incbin "recovery/artifacts/firmware.preliminary.bin", 23276, 20
.global fn_08005b00
.type fn_08005b00,%function
.thumb_func
fn_08005b00:
.incbin "recovery/artifacts/firmware.preliminary.bin", 23296, 124
.global fn_08005b7c
.type fn_08005b7c,%function
.thumb_func
fn_08005b7c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 23420, 40
.global fn_08005ba4
.type fn_08005ba4,%function
.thumb_func
fn_08005ba4:
.incbin "recovery/artifacts/firmware.preliminary.bin", 23460, 16
.global fn_08005bb4
.type fn_08005bb4,%function
.thumb_func
fn_08005bb4:
.incbin "recovery/artifacts/firmware.preliminary.bin", 23476, 24
.global fn_08005bcc
.type fn_08005bcc,%function
.thumb_func
fn_08005bcc:
.incbin "recovery/artifacts/firmware.preliminary.bin", 23500, 368
.global fn_08005d3c
.type fn_08005d3c,%function
.thumb_func
fn_08005d3c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 23868, 10
.global fn_08005d46
.type fn_08005d46,%function
.thumb_func
fn_08005d46:
.incbin "recovery/artifacts/firmware.preliminary.bin", 23878, 14
.global fn_08005d54
.type fn_08005d54,%function
.thumb_func
fn_08005d54:
.incbin "recovery/artifacts/firmware.preliminary.bin", 23892, 12
.global fn_08005d60
.type fn_08005d60,%function
.thumb_func
fn_08005d60:
.incbin "recovery/artifacts/firmware.preliminary.bin", 23904, 74
.global fn_08005daa
.type fn_08005daa,%function
.thumb_func
fn_08005daa:
.incbin "recovery/artifacts/firmware.preliminary.bin", 23978, 74
.global fn_08005df4
.type fn_08005df4,%function
.thumb_func
fn_08005df4:
.incbin "recovery/artifacts/firmware.preliminary.bin", 24052, 180
.global fn_08005ea8
.type fn_08005ea8,%function
.thumb_func
fn_08005ea8:
.incbin "recovery/artifacts/firmware.preliminary.bin", 24232, 272
.global fn_08005fb8
.type fn_08005fb8,%function
.thumb_func
fn_08005fb8:
.incbin "recovery/artifacts/firmware.preliminary.bin", 24504, 340
.global fn_0800610c
.type fn_0800610c,%function
.thumb_func
fn_0800610c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 24844, 332
.global fn_08006258
.type fn_08006258,%function
.thumb_func
fn_08006258:
.incbin "recovery/artifacts/firmware.preliminary.bin", 25176, 100
.global fn_080062bc
.type fn_080062bc,%function
.thumb_func
fn_080062bc:
.incbin "recovery/artifacts/firmware.preliminary.bin", 25276, 100
.global fn_08006320
.type fn_08006320,%function
.thumb_func
fn_08006320:
.incbin "recovery/artifacts/firmware.preliminary.bin", 25376, 16
.global fn_08006330
.type fn_08006330,%function
.thumb_func
fn_08006330:
.incbin "recovery/artifacts/firmware.preliminary.bin", 25392, 16
.global fn_08006340
.type fn_08006340,%function
.thumb_func
fn_08006340:
.incbin "recovery/artifacts/firmware.preliminary.bin", 25408, 32
.global fn_08006360
.type fn_08006360,%function
.thumb_func
fn_08006360:
.incbin "recovery/artifacts/firmware.preliminary.bin", 25440, 68
.global fn_080063a4
.type fn_080063a4,%function
.thumb_func
fn_080063a4:
.incbin "recovery/artifacts/firmware.preliminary.bin", 25508, 40
.global fn_080063cc
.type fn_080063cc,%function
.thumb_func
fn_080063cc:
.incbin "recovery/artifacts/firmware.preliminary.bin", 25548, 24
.global fn_080063e4
.type fn_080063e4,%function
.thumb_func
fn_080063e4:
.incbin "recovery/artifacts/firmware.preliminary.bin", 25572, 8
.global fn_080063ec
.type fn_080063ec,%function
.thumb_func
fn_080063ec:
.incbin "recovery/artifacts/firmware.preliminary.bin", 25580, 28
.global fn_08006408
.type fn_08006408,%function
.thumb_func
fn_08006408:
.incbin "recovery/artifacts/firmware.preliminary.bin", 25608, 232
.global fn_080064f0
.type fn_080064f0,%function
.thumb_func
fn_080064f0:
.incbin "recovery/artifacts/firmware.preliminary.bin", 25840, 264
.global fn_080065f8
.type fn_080065f8,%function
.thumb_func
fn_080065f8:
.incbin "recovery/artifacts/firmware.preliminary.bin", 26104, 32
.global fn_08006618
.type fn_08006618,%function
.thumb_func
fn_08006618:
.incbin "recovery/artifacts/firmware.preliminary.bin", 26136, 128
.global fn_08006698
.type fn_08006698,%function
.thumb_func
fn_08006698:
.incbin "recovery/artifacts/firmware.preliminary.bin", 26264, 904
.global fn_08006a20
.type fn_08006a20,%function
.thumb_func
fn_08006a20:
.incbin "recovery/artifacts/firmware.preliminary.bin", 27168, 48
.global fn_08006a50
.type fn_08006a50,%function
.thumb_func
fn_08006a50:
.incbin "recovery/artifacts/firmware.preliminary.bin", 27216, 2
.global fn_08006a52
.type fn_08006a52,%function
.thumb_func
fn_08006a52:
.incbin "recovery/artifacts/firmware.preliminary.bin", 27218, 2
.global fn_08006a54
.type fn_08006a54,%function
.thumb_func
fn_08006a54:
.incbin "recovery/artifacts/firmware.preliminary.bin", 27220, 92
.global fn_08006ab0
.type fn_08006ab0,%function
.thumb_func
fn_08006ab0:
.incbin "recovery/artifacts/firmware.preliminary.bin", 27312, 72
.global fn_08006af8
.type fn_08006af8,%function
.thumb_func
fn_08006af8:
.incbin "recovery/artifacts/firmware.preliminary.bin", 27384, 52
.global fn_08006b2c
.type fn_08006b2c,%function
.thumb_func
fn_08006b2c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 27436, 80
.global fn_08006b7c
.type fn_08006b7c,%function
.thumb_func
fn_08006b7c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 27516, 208
.global fn_08006c4c
.type fn_08006c4c,%function
.thumb_func
fn_08006c4c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 27724, 2
.global fn_08006c4e
.type fn_08006c4e,%function
.thumb_func
fn_08006c4e:
.incbin "recovery/artifacts/firmware.preliminary.bin", 27726, 354
.global fn_08006db0
.type fn_08006db0,%function
.thumb_func
fn_08006db0:
.incbin "recovery/artifacts/firmware.preliminary.bin", 28080, 2
.global fn_08006db2
.type fn_08006db2,%function
.thumb_func
fn_08006db2:
.incbin "recovery/artifacts/firmware.preliminary.bin", 28082, 2
.global fn_08006db4
.type fn_08006db4,%function
.thumb_func
fn_08006db4:
.incbin "recovery/artifacts/firmware.preliminary.bin", 28084, 20
.global fn_08006dc8
.type fn_08006dc8,%function
.thumb_func
fn_08006dc8:
.incbin "recovery/artifacts/firmware.preliminary.bin", 28104, 2
.global fn_08006dca
.type fn_08006dca,%function
.thumb_func
fn_08006dca:
.incbin "recovery/artifacts/firmware.preliminary.bin", 28106, 94
.global fn_08006e28
.type fn_08006e28,%function
.thumb_func
fn_08006e28:
.incbin "recovery/artifacts/firmware.preliminary.bin", 28200, 60
.global fn_08006e64
.type fn_08006e64,%function
.thumb_func
fn_08006e64:
.incbin "recovery/artifacts/firmware.preliminary.bin", 28260, 60
.global fn_08006ea0
.type fn_08006ea0,%function
.thumb_func
fn_08006ea0:
.incbin "recovery/artifacts/firmware.preliminary.bin", 28320, 520
.global fn_080070a8
.type fn_080070a8,%function
.thumb_func
fn_080070a8:
.incbin "recovery/artifacts/firmware.preliminary.bin", 28840, 108
.global fn_08007114
.type fn_08007114,%function
.thumb_func
fn_08007114:
.incbin "recovery/artifacts/firmware.preliminary.bin", 28948, 360
.global fn_0800727c
.type fn_0800727c,%function
.thumb_func
fn_0800727c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 29308, 2
.global fn_0800727e
.type fn_0800727e,%function
.thumb_func
fn_0800727e:
.incbin "recovery/artifacts/firmware.preliminary.bin", 29310, 2
.global fn_08007280
.type fn_08007280,%function
.thumb_func
fn_08007280:
.incbin "recovery/artifacts/firmware.preliminary.bin", 29312, 176
.global fn_08007330
.type fn_08007330,%function
.thumb_func
fn_08007330:
.incbin "recovery/artifacts/firmware.preliminary.bin", 29488, 44
.global fn_0800735c
.type fn_0800735c,%function
.thumb_func
fn_0800735c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 29532, 2
.global fn_0800735e
.type fn_0800735e,%function
.thumb_func
fn_0800735e:
.incbin "recovery/artifacts/firmware.preliminary.bin", 29534, 138
.global fn_080073e8
.type fn_080073e8,%function
.thumb_func
fn_080073e8:
.incbin "recovery/artifacts/firmware.preliminary.bin", 29672, 24
.global fn_08007400
.type fn_08007400,%function
.thumb_func
fn_08007400:
.incbin "recovery/artifacts/firmware.preliminary.bin", 29696, 80
.global fn_08007450
.type fn_08007450,%function
.thumb_func
fn_08007450:
.incbin "recovery/artifacts/firmware.preliminary.bin", 29776, 36
.global fn_08007474
.type fn_08007474,%function
.thumb_func
fn_08007474:
.incbin "recovery/artifacts/firmware.preliminary.bin", 29812, 32
.global fn_08007494
.type fn_08007494,%function
.thumb_func
fn_08007494:
.incbin "recovery/artifacts/firmware.preliminary.bin", 29844, 4
.global fn_08007498
.type fn_08007498,%function
.thumb_func
fn_08007498:
.incbin "recovery/artifacts/firmware.preliminary.bin", 29848, 44
.global fn_080074c4
.type fn_080074c4,%function
.thumb_func
fn_080074c4:
.incbin "recovery/artifacts/firmware.preliminary.bin", 29892, 56
.global fn_080074fc
.type fn_080074fc,%function
.thumb_func
fn_080074fc:
.incbin "recovery/artifacts/firmware.preliminary.bin", 29948, 220
.global fn_080075d8
.type fn_080075d8,%function
.thumb_func
fn_080075d8:
.incbin "recovery/artifacts/firmware.preliminary.bin", 30168, 36
.global fn_080075fc
.type fn_080075fc,%function
.thumb_func
fn_080075fc:
.incbin "recovery/artifacts/firmware.preliminary.bin", 30204, 112
.global fn_0800766c
.type fn_0800766c,%function
.thumb_func
fn_0800766c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 30316, 96
.global fn_080076cc
.type fn_080076cc,%function
.thumb_func
fn_080076cc:
.incbin "recovery/artifacts/firmware.preliminary.bin", 30412, 96
.global fn_0800772c
.type fn_0800772c,%function
.thumb_func
fn_0800772c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 30508, 40
.global fn_08007754
.type fn_08007754,%function
.thumb_func
fn_08007754:
.incbin "recovery/artifacts/firmware.preliminary.bin", 30548, 78
.global fn_080077a2
.type fn_080077a2,%function
.thumb_func
fn_080077a2:
.incbin "recovery/artifacts/firmware.preliminary.bin", 30626, 76
.global fn_080077ee
.type fn_080077ee,%function
.thumb_func
fn_080077ee:
.incbin "recovery/artifacts/firmware.preliminary.bin", 30702, 82
.global fn_08007840
.type fn_08007840,%function
.thumb_func
fn_08007840:
.incbin "recovery/artifacts/firmware.preliminary.bin", 30784, 96
.global fn_080078a0
.type fn_080078a0,%function
.thumb_func
fn_080078a0:
.incbin "recovery/artifacts/firmware.preliminary.bin", 30880, 100
.global fn_08007904
.type fn_08007904,%function
.thumb_func
fn_08007904:
.incbin "recovery/artifacts/firmware.preliminary.bin", 30980, 1004
.global fn_08007cf0
.type fn_08007cf0,%function
.thumb_func
fn_08007cf0:
.incbin "recovery/artifacts/firmware.preliminary.bin", 31984, 84
.global fn_08007d44
.type fn_08007d44,%function
.thumb_func
fn_08007d44:
.incbin "recovery/artifacts/firmware.preliminary.bin", 32068, 108
.global fn_08007db0
.type fn_08007db0,%function
.thumb_func
fn_08007db0:
.incbin "recovery/artifacts/firmware.preliminary.bin", 32176, 56
.global fn_08007de8
.type fn_08007de8,%function
.thumb_func
fn_08007de8:
.incbin "recovery/artifacts/firmware.preliminary.bin", 32232, 336
.global fn_08007f38
.type fn_08007f38,%function
.thumb_func
fn_08007f38:
.incbin "recovery/artifacts/firmware.preliminary.bin", 32568, 88
.global fn_08007f90
.type fn_08007f90,%function
.thumb_func
fn_08007f90:
.incbin "recovery/artifacts/firmware.preliminary.bin", 32656, 52
.global fn_08007fc4
.type fn_08007fc4,%function
.thumb_func
fn_08007fc4:
.incbin "recovery/artifacts/firmware.preliminary.bin", 32708, 112
.global fn_08008034
.type fn_08008034,%function
.thumb_func
fn_08008034:
.incbin "recovery/artifacts/firmware.preliminary.bin", 32820, 56
.global fn_0800806c
.type fn_0800806c,%function
.thumb_func
fn_0800806c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 32876, 56
.global fn_080080a4
.type fn_080080a4,%function
.thumb_func
fn_080080a4:
.incbin "recovery/artifacts/firmware.preliminary.bin", 32932, 4
.global fn_080080a8
.type fn_080080a8,%function
.thumb_func
fn_080080a8:
.incbin "recovery/artifacts/firmware.preliminary.bin", 32936, 380
.global fn_08008224
.type fn_08008224,%function
.thumb_func
fn_08008224:
.incbin "recovery/artifacts/firmware.preliminary.bin", 33316, 56
.global fn_0800825c
.type fn_0800825c,%function
.thumb_func
fn_0800825c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 33372, 2
.global fn_0800825e
.type fn_0800825e,%function
.thumb_func
fn_0800825e:
.incbin "recovery/artifacts/firmware.preliminary.bin", 33374, 26
.global fn_08008278
.type fn_08008278,%function
.thumb_func
fn_08008278:
.incbin "recovery/artifacts/firmware.preliminary.bin", 33400, 112
.global fn_080082e8
.type fn_080082e8,%function
.thumb_func
fn_080082e8:
.incbin "recovery/artifacts/firmware.preliminary.bin", 33512, 388
.global fn_0800846c
.type fn_0800846c,%function
.thumb_func
fn_0800846c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 33900, 20
.global fn_08008480
.type fn_08008480,%function
.thumb_func
fn_08008480:
.incbin "recovery/artifacts/firmware.preliminary.bin", 33920, 2
.global fn_08008482
.type fn_08008482,%function
.thumb_func
fn_08008482:
.incbin "recovery/artifacts/firmware.preliminary.bin", 33922, 8
.global fn_0800848a
.type fn_0800848a,%function
.thumb_func
fn_0800848a:
.incbin "recovery/artifacts/firmware.preliminary.bin", 33930, 130
.global fn_0800850c
.type fn_0800850c,%function
.thumb_func
fn_0800850c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 34060, 16
.global fn_0800851c
.type fn_0800851c,%function
.thumb_func
fn_0800851c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 34076, 136
.global fn_080085a4
.type fn_080085a4,%function
.thumb_func
fn_080085a4:
.incbin "recovery/artifacts/firmware.preliminary.bin", 34212, 22
.global fn_080085ba
.type fn_080085ba,%function
.thumb_func
fn_080085ba:
.incbin "recovery/artifacts/firmware.preliminary.bin", 34234, 16
.global fn_080085ca
.type fn_080085ca,%function
.thumb_func
fn_080085ca:
.incbin "recovery/artifacts/firmware.preliminary.bin", 34250, 34
.global fn_080085ec
.type fn_080085ec,%function
.thumb_func
fn_080085ec:
.incbin "recovery/artifacts/firmware.preliminary.bin", 34284, 40
.global fn_08008614
.type fn_08008614,%function
.thumb_func
fn_08008614:
.incbin "recovery/artifacts/firmware.preliminary.bin", 34324, 164
.global fn_080086b8
.type fn_080086b8,%function
.thumb_func
fn_080086b8:
.incbin "recovery/artifacts/firmware.preliminary.bin", 34488, 24
.global fn_080086d0
.type fn_080086d0,%function
.thumb_func
fn_080086d0:
.incbin "recovery/artifacts/firmware.preliminary.bin", 34512, 88
.global fn_08008728
.type fn_08008728,%function
.thumb_func
fn_08008728:
.incbin "recovery/artifacts/firmware.preliminary.bin", 34600, 24
.global fn_08008740
.type fn_08008740,%function
.thumb_func
fn_08008740:
.incbin "recovery/artifacts/firmware.preliminary.bin", 34624, 108
.global fn_080087ac
.type fn_080087ac,%function
.thumb_func
fn_080087ac:
.incbin "recovery/artifacts/firmware.preliminary.bin", 34732, 12
.global fn_080087b8
.type fn_080087b8,%function
.thumb_func
fn_080087b8:
.incbin "recovery/artifacts/firmware.preliminary.bin", 34744, 28
.global fn_080087d4
.type fn_080087d4,%function
.thumb_func
fn_080087d4:
.incbin "recovery/artifacts/firmware.preliminary.bin", 34772, 88
.global fn_0800882c
.type fn_0800882c,%function
.thumb_func
fn_0800882c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 34860, 100
.global fn_08008890
.type fn_08008890,%function
.thumb_func
fn_08008890:
.incbin "recovery/artifacts/firmware.preliminary.bin", 34960, 124
.global fn_0800890c
.type fn_0800890c,%function
.thumb_func
fn_0800890c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 35084, 1220
.global fn_08008dd0
.type fn_08008dd0,%function
.thumb_func
fn_08008dd0:
.incbin "recovery/artifacts/firmware.preliminary.bin", 36304, 180
.global fn_08008e84
.type fn_08008e84,%function
.thumb_func
fn_08008e84:
.incbin "recovery/artifacts/firmware.preliminary.bin", 36484, 40
.global fn_08008eac
.type fn_08008eac,%function
.thumb_func
fn_08008eac:
.incbin "recovery/artifacts/firmware.preliminary.bin", 36524, 216
.global fn_08008f84
.type fn_08008f84,%function
.thumb_func
fn_08008f84:
.incbin "recovery/artifacts/firmware.preliminary.bin", 36740, 204
.global fn_08009050
.type fn_08009050,%function
.thumb_func
fn_08009050:
.incbin "recovery/artifacts/firmware.preliminary.bin", 36944, 372
.global fn_080091c4
.type fn_080091c4,%function
.thumb_func
fn_080091c4:
.incbin "recovery/artifacts/firmware.preliminary.bin", 37316, 50
.global fn_080091f6
.type fn_080091f6,%function
.thumb_func
fn_080091f6:
.incbin "recovery/artifacts/firmware.preliminary.bin", 37366, 18
.global fn_08009208
.type fn_08009208,%function
.thumb_func
fn_08009208:
.incbin "recovery/artifacts/firmware.preliminary.bin", 37384, 308
.global fn_0800933c
.type fn_0800933c,%function
.thumb_func
fn_0800933c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 37692, 140
.global fn_080093c8
.type fn_080093c8,%function
.thumb_func
fn_080093c8:
.incbin "recovery/artifacts/firmware.preliminary.bin", 37832, 160
.global fn_08009468
.type fn_08009468,%function
.thumb_func
fn_08009468:
.incbin "recovery/artifacts/firmware.preliminary.bin", 37992, 20
.global fn_0800947c
.type fn_0800947c,%function
.thumb_func
fn_0800947c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 38012, 40
.global fn_080094a4
.type fn_080094a4,%function
.thumb_func
fn_080094a4:
.incbin "recovery/artifacts/firmware.preliminary.bin", 38052, 16
.global fn_080094b4
.type fn_080094b4,%function
.thumb_func
fn_080094b4:
.incbin "recovery/artifacts/firmware.preliminary.bin", 38068, 36
.global fn_080094d8
.type fn_080094d8,%function
.thumb_func
fn_080094d8:
.incbin "recovery/artifacts/firmware.preliminary.bin", 38104, 16
.global fn_080094e8
.type fn_080094e8,%function
.thumb_func
fn_080094e8:
.incbin "recovery/artifacts/firmware.preliminary.bin", 38120, 140
.global fn_08009574
.type fn_08009574,%function
.thumb_func
fn_08009574:
.incbin "recovery/artifacts/firmware.preliminary.bin", 38260, 46
.global fn_080095a2
.type fn_080095a2,%function
.thumb_func
fn_080095a2:
.incbin "recovery/artifacts/firmware.preliminary.bin", 38306, 48
.global fn_080095d2
.type fn_080095d2,%function
.thumb_func
fn_080095d2:
.incbin "recovery/artifacts/firmware.preliminary.bin", 38354, 26
.global fn_080095ec
.type fn_080095ec,%function
.thumb_func
fn_080095ec:
.incbin "recovery/artifacts/firmware.preliminary.bin", 38380, 98
.global fn_0800964e
.type fn_0800964e,%function
.thumb_func
fn_0800964e:
.incbin "recovery/artifacts/firmware.preliminary.bin", 38478, 70
.global fn_08009694
.type fn_08009694,%function
.thumb_func
fn_08009694:
.incbin "recovery/artifacts/firmware.preliminary.bin", 38548, 1648
.global fn_08009d04
.type fn_08009d04,%function
.thumb_func
fn_08009d04:
.incbin "recovery/artifacts/firmware.preliminary.bin", 40196, 76
.global fn_08009d50
.type fn_08009d50,%function
.thumb_func
fn_08009d50:
.incbin "recovery/artifacts/firmware.preliminary.bin", 40272, 52
.global fn_08009d84
.type fn_08009d84,%function
.thumb_func
fn_08009d84:
.incbin "recovery/artifacts/firmware.preliminary.bin", 40324, 144
.global fn_08009e14
.type fn_08009e14,%function
.thumb_func
fn_08009e14:
.incbin "recovery/artifacts/firmware.preliminary.bin", 40468, 28
.global fn_08009e30
.type fn_08009e30,%function
.thumb_func
fn_08009e30:
.incbin "recovery/artifacts/firmware.preliminary.bin", 40496, 276
.global fn_08009f44
.type fn_08009f44,%function
.thumb_func
fn_08009f44:
.incbin "recovery/artifacts/firmware.preliminary.bin", 40772, 68
.global fn_08009f88
.type fn_08009f88,%function
.thumb_func
fn_08009f88:
.incbin "recovery/artifacts/firmware.preliminary.bin", 40840, 28
.global fn_08009fa4
.type fn_08009fa4,%function
.thumb_func
fn_08009fa4:
.incbin "recovery/artifacts/firmware.preliminary.bin", 40868, 32
.global fn_08009fc4
.type fn_08009fc4,%function
.thumb_func
fn_08009fc4:
.incbin "recovery/artifacts/firmware.preliminary.bin", 40900, 40
.global fn_08009fec
.type fn_08009fec,%function
.thumb_func
fn_08009fec:
.incbin "recovery/artifacts/firmware.preliminary.bin", 40940, 44
.global fn_0800a018
.type fn_0800a018,%function
.thumb_func
fn_0800a018:
.incbin "recovery/artifacts/firmware.preliminary.bin", 40984, 60
.global fn_0800a054
.type fn_0800a054,%function
.thumb_func
fn_0800a054:
.incbin "recovery/artifacts/firmware.preliminary.bin", 41044, 20
.global fn_0800a068
.type fn_0800a068,%function
.thumb_func
fn_0800a068:
.incbin "recovery/artifacts/firmware.preliminary.bin", 41064, 40
.global fn_0800a090
.type fn_0800a090,%function
.thumb_func
fn_0800a090:
.incbin "recovery/artifacts/firmware.preliminary.bin", 41104, 152
.global fn_0800a128
.type fn_0800a128,%function
.thumb_func
fn_0800a128:
.incbin "recovery/artifacts/firmware.preliminary.bin", 41256, 192
.global fn_0800a1e8
.type fn_0800a1e8,%function
.thumb_func
fn_0800a1e8:
.incbin "recovery/artifacts/firmware.preliminary.bin", 41448, 100
.global fn_0800a24c
.type fn_0800a24c,%function
.thumb_func
fn_0800a24c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 41548, 132
.global fn_0800a2d0
.type fn_0800a2d0,%function
.thumb_func
fn_0800a2d0:
.incbin "recovery/artifacts/firmware.preliminary.bin", 41680, 176
.global fn_0800a380
.type fn_0800a380,%function
.thumb_func
fn_0800a380:
.incbin "recovery/artifacts/firmware.preliminary.bin", 41856, 12
.global fn_0800a38c
.type fn_0800a38c,%function
.thumb_func
fn_0800a38c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 41868, 76
.global fn_0800a3d8
.type fn_0800a3d8,%function
.thumb_func
fn_0800a3d8:
.incbin "recovery/artifacts/firmware.preliminary.bin", 41944, 28
.global fn_0800a3f4
.type fn_0800a3f4,%function
.thumb_func
fn_0800a3f4:
.incbin "recovery/artifacts/firmware.preliminary.bin", 41972, 92
.global fn_0800a450
.type fn_0800a450,%function
.thumb_func
fn_0800a450:
.incbin "recovery/artifacts/firmware.preliminary.bin", 42064, 28
.global fn_0800a46c
.type fn_0800a46c,%function
.thumb_func
fn_0800a46c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 42092, 16
.global fn_0800a47c
.type fn_0800a47c,%function
.thumb_func
fn_0800a47c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 42108, 12
.global fn_0800a488
.type fn_0800a488,%function
.thumb_func
fn_0800a488:
.incbin "recovery/artifacts/firmware.preliminary.bin", 42120, 32
.global fn_0800a4a8
.type fn_0800a4a8,%function
.thumb_func
fn_0800a4a8:
.incbin "recovery/artifacts/firmware.preliminary.bin", 42152, 12
.global fn_0800a4b4
.type fn_0800a4b4,%function
.thumb_func
fn_0800a4b4:
.incbin "recovery/artifacts/firmware.preliminary.bin", 42164, 40
.global fn_0800a4dc
.type fn_0800a4dc,%function
.thumb_func
fn_0800a4dc:
.incbin "recovery/artifacts/firmware.preliminary.bin", 42204, 212
.global fn_0800a5b0
.type fn_0800a5b0,%function
.thumb_func
fn_0800a5b0:
.incbin "recovery/artifacts/firmware.preliminary.bin", 42416, 148
.global fn_0800a644
.type fn_0800a644,%function
.thumb_func
fn_0800a644:
.incbin "recovery/artifacts/firmware.preliminary.bin", 42564, 24
.global fn_0800a65c
.type fn_0800a65c,%function
.thumb_func
fn_0800a65c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 42588, 52
.global fn_0800a690
.type fn_0800a690,%function
.thumb_func
fn_0800a690:
.incbin "recovery/artifacts/firmware.preliminary.bin", 42640, 16
.global fn_0800a6a0
.type fn_0800a6a0,%function
.thumb_func
fn_0800a6a0:
.incbin "recovery/artifacts/firmware.preliminary.bin", 42656, 44
.global fn_0800a6cc
.type fn_0800a6cc,%function
.thumb_func
fn_0800a6cc:
.incbin "recovery/artifacts/firmware.preliminary.bin", 42700, 16
.global fn_0800a6dc
.type fn_0800a6dc,%function
.thumb_func
fn_0800a6dc:
.incbin "recovery/artifacts/firmware.preliminary.bin", 42716, 44
.global app_main
.type app_main,%function
.thumb_func
app_main:
.incbin "recovery/artifacts/firmware.preliminary.bin", 42760, 204
.global fn_0800a7d4
.type fn_0800a7d4,%function
.thumb_func
fn_0800a7d4:
.incbin "recovery/artifacts/firmware.preliminary.bin", 42964, 2312
.global fn_0800b0dc
.type fn_0800b0dc,%function
.thumb_func
fn_0800b0dc:
.incbin "recovery/artifacts/firmware.preliminary.bin", 45276, 1528
.global fn_0800b6d4
.type fn_0800b6d4,%function
.thumb_func
fn_0800b6d4:
.incbin "recovery/artifacts/firmware.preliminary.bin", 46804, 52
.global fn_0800b708
.type fn_0800b708,%function
.thumb_func
fn_0800b708:
.incbin "recovery/artifacts/firmware.preliminary.bin", 46856, 68
.global fn_0800b74c
.type fn_0800b74c,%function
.thumb_func
fn_0800b74c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 46924, 92
.global fn_0800b7a8
.type fn_0800b7a8,%function
.thumb_func
fn_0800b7a8:
.incbin "recovery/artifacts/firmware.preliminary.bin", 47016, 212
.global fn_0800b87c
.type fn_0800b87c,%function
.thumb_func
fn_0800b87c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 47228, 228
.global fn_0800b960
.type fn_0800b960,%function
.thumb_func
fn_0800b960:
.incbin "recovery/artifacts/firmware.preliminary.bin", 47456, 288
.global fn_0800ba80
.type fn_0800ba80,%function
.thumb_func
fn_0800ba80:
.incbin "recovery/artifacts/firmware.preliminary.bin", 47744, 52
.global fn_0800bab4
.type fn_0800bab4,%function
.thumb_func
fn_0800bab4:
.incbin "recovery/artifacts/firmware.preliminary.bin", 47796, 144
.global fn_0800bb44
.type fn_0800bb44,%function
.thumb_func
fn_0800bb44:
.incbin "recovery/artifacts/firmware.preliminary.bin", 47940, 56
.global fn_0800bb7c
.type fn_0800bb7c,%function
.thumb_func
fn_0800bb7c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 47996, 188
.global fn_0800bc38
.type fn_0800bc38,%function
.thumb_func
fn_0800bc38:
.incbin "recovery/artifacts/firmware.preliminary.bin", 48184, 60
.global fn_0800bc74
.type fn_0800bc74,%function
.thumb_func
fn_0800bc74:
.incbin "recovery/artifacts/firmware.preliminary.bin", 48244, 56
.global fn_0800bcac
.type fn_0800bcac,%function
.thumb_func
fn_0800bcac:
.incbin "recovery/artifacts/firmware.preliminary.bin", 48300, 44
.global fn_0800bcd8
.type fn_0800bcd8,%function
.thumb_func
fn_0800bcd8:
.incbin "recovery/artifacts/firmware.preliminary.bin", 48344, 332
.global fn_0800be24
.type fn_0800be24,%function
.thumb_func
fn_0800be24:
.incbin "recovery/artifacts/firmware.preliminary.bin", 48676, 932
.global fn_0800c1c8
.type fn_0800c1c8,%function
.thumb_func
fn_0800c1c8:
.incbin "recovery/artifacts/firmware.preliminary.bin", 49608, 68
.global fn_0800c20c
.type fn_0800c20c,%function
.thumb_func
fn_0800c20c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 49676, 140
.global fn_0800c298
.type fn_0800c298,%function
.thumb_func
fn_0800c298:
.incbin "recovery/artifacts/firmware.preliminary.bin", 49816, 1088
.global fn_0800c6d8
.type fn_0800c6d8,%function
.thumb_func
fn_0800c6d8:
.incbin "recovery/artifacts/firmware.preliminary.bin", 50904, 20
.global fn_0800c6ec
.type fn_0800c6ec,%function
.thumb_func
fn_0800c6ec:
.incbin "recovery/artifacts/firmware.preliminary.bin", 50924, 32
.global fn_0800c70c
.type fn_0800c70c,%function
.thumb_func
fn_0800c70c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 50956, 124
.global fn_0800c788
.type fn_0800c788,%function
.thumb_func
fn_0800c788:
.incbin "recovery/artifacts/firmware.preliminary.bin", 51080, 60
.global fn_0800c7c4
.type fn_0800c7c4,%function
.thumb_func
fn_0800c7c4:
.incbin "recovery/artifacts/firmware.preliminary.bin", 51140, 80
.global fn_0800c814
.type fn_0800c814,%function
.thumb_func
fn_0800c814:
.incbin "recovery/artifacts/firmware.preliminary.bin", 51220, 28
.global fn_0800c830
.type fn_0800c830,%function
.thumb_func
fn_0800c830:
.incbin "recovery/artifacts/firmware.preliminary.bin", 51248, 44
.global fn_0800c85c
.type fn_0800c85c,%function
.thumb_func
fn_0800c85c:
.incbin "recovery/artifacts/firmware.preliminary.bin", 51292, 472
.global fn_0800ca34
.type fn_0800ca34,%function
.thumb_func
fn_0800ca34:
.incbin "recovery/artifacts/firmware.preliminary.bin", 51764, 76
.global fn_0800ca80
.type fn_0800ca80,%function
.thumb_func
fn_0800ca80:
.incbin "recovery/artifacts/firmware.preliminary.bin", 51840, 452
.global fn_0800cc44
.type fn_0800cc44,%function
.thumb_func
fn_0800cc44:
.incbin "recovery/artifacts/firmware.preliminary.bin", 52292, 32
.global fn_0800cc64
.type fn_0800cc64,%function
.thumb_func
fn_0800cc64:
.incbin "recovery/artifacts/firmware.preliminary.bin", 52324, 28
.global fn_0800cc80
.type fn_0800cc80,%function
.thumb_func
fn_0800cc80:
.incbin "recovery/artifacts/firmware.preliminary.bin", 52352, 192
.global fn_0800cd40
.type fn_0800cd40,%function
.thumb_func
fn_0800cd40:
.incbin "recovery/artifacts/firmware.preliminary.bin", 52544, 100
.global fn_0800cda4
.type fn_0800cda4,%function
.thumb_func
fn_0800cda4:
.incbin "recovery/artifacts/firmware.preliminary.bin", 52644, 20
.global fn_0800cdb8
.type fn_0800cdb8,%function
.thumb_func
fn_0800cdb8:
.incbin "recovery/artifacts/firmware.preliminary.bin", 52664, 12872
