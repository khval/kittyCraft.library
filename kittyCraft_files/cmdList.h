
struct cmdData
{
	unsigned short token;
	char *name;
	int args;
	char *(*fn) KITTENS_CMD_ARGS;
};


extern char *craftAmosBase KITTENS_CMD_ARGS;
extern char *craftAmosPri KITTENS_CMD_ARGS;
extern char *craftAmosPro KITTENS_CMD_ARGS;
extern char *craftB_swap KITTENS_CMD_ARGS;
extern char *craftBankColour KITTENS_CMD_ARGS;
extern char *craftBeamWait KITTENS_CMD_ARGS;
extern char *craftBwInstr KITTENS_CMD_ARGS;
extern char *craftChipMaxBlock KITTENS_CMD_ARGS;
extern char *craftChrConvSTR KITTENS_CMD_ARGS;
extern char *craftChrDumpSTR KITTENS_CMD_ARGS;
extern char *craftCliExecute KITTENS_CMD_ARGS;
extern char *craftCliHere KITTENS_CMD_ARGS;
extern char *craftCliPrint KITTENS_CMD_ARGS;
extern char *craftCraftVersion KITTENS_CMD_ARGS;
extern char *craftDbFree KITTENS_CMD_ARGS;
extern char *craftDbSize KITTENS_CMD_ARGS;
extern char *craftDbUsed KITTENS_CMD_ARGS;
extern char *craftDelBankColour KITTENS_CMD_ARGS;
extern char *craftDiscError KITTENS_CMD_ARGS;
extern char *craftDiscState KITTENS_CMD_ARGS;
extern char *craftDiscTypeSTR KITTENS_CMD_ARGS;
extern char *craftDrCommentSTR KITTENS_CMD_ARGS;
extern char *craftDrFib KITTENS_CMD_ARGS;
extern char *craftDrFileSTR KITTENS_CMD_ARGS;
extern char *craftDrForget KITTENS_CMD_ARGS;
extern char *craftDrLength KITTENS_CMD_ARGS;
extern char *craftDrNameSTR KITTENS_CMD_ARGS;
extern char *craftDrNextSTR KITTENS_CMD_ARGS;
extern char *craftDrPathSTR KITTENS_CMD_ARGS;
extern char *craftDrProtect KITTENS_CMD_ARGS;
extern char *craftDrType KITTENS_CMD_ARGS;
extern char *craftFastMaxBlock KITTENS_CMD_ARGS;
extern char *craftFileCommentSTR KITTENS_CMD_ARGS;
extern char *craftFileLength KITTENS_CMD_ARGS;
extern char *craftFileProtect KITTENS_CMD_ARGS;
extern char *craftFileType KITTENS_CMD_ARGS;
extern char *craftFlipCaseSTR KITTENS_CMD_ARGS;
extern char *craftFrColour KITTENS_CMD_ARGS;
extern char *craftFrGetColour KITTENS_CMD_ARGS;
extern char *craftFrJulia KITTENS_CMD_ARGS;
extern char *craftFrMandelbrot KITTENS_CMD_ARGS;
extern char *craftFrPosition KITTENS_CMD_ARGS;
extern char *craftFrReset KITTENS_CMD_ARGS;
extern char *craftFrScan KITTENS_CMD_ARGS;
extern char *craftFrScanAll KITTENS_CMD_ARGS;
extern char *craftFrStep KITTENS_CMD_ARGS;
extern char *craftFrWindow KITTENS_CMD_ARGS;
extern char *craftFrXPosition KITTENS_CMD_ARGS;
extern char *craftFrXStep KITTENS_CMD_ARGS;
extern char *craftFrYPosition KITTENS_CMD_ARGS;
extern char *craftFrYStep KITTENS_CMD_ARGS;
extern char *craftGrBack KITTENS_CMD_ARGS;
extern char *craftGrBorder KITTENS_CMD_ARGS;
extern char *craftGrCentre KITTENS_CMD_ARGS;
extern char *craftGrInk KITTENS_CMD_ARGS;
extern char *craftGuruAlert KITTENS_CMD_ARGS;
extern char *craftGuruMeditation KITTENS_CMD_ARGS;
extern char *craftHardReset KITTENS_CMD_ARGS;
extern char *craftHexDumpSTR KITTENS_CMD_ARGS;
extern char *craftHwMouseKey KITTENS_CMD_ARGS;
extern char *craftL_swap KITTENS_CMD_ARGS;
extern char *craftLeftTrimSTR KITTENS_CMD_ARGS;
extern char *craftLoCaseSTR KITTENS_CMD_ARGS;
extern char *craftMemCopy KITTENS_CMD_ARGS;
extern char *craftMemScramble KITTENS_CMD_ARGS;
extern char *craftMemStrCount KITTENS_CMD_ARGS;
extern char *craftMemType KITTENS_CMD_ARGS;
extern char *craftMemUnscramble KITTENS_CMD_ARGS;
extern char *craftMultiOff KITTENS_CMD_ARGS;
extern char *craftMultiOn KITTENS_CMD_ARGS;
extern char *craftOpenWorkbench KITTENS_CMD_ARGS;
extern char *craftPalBlue KITTENS_CMD_ARGS;
extern char *craftPalCopy KITTENS_CMD_ARGS;
extern char *craftPalCount KITTENS_CMD_ARGS;
extern char *craftPalFromBank KITTENS_CMD_ARGS;
extern char *craftPalGreen KITTENS_CMD_ARGS;
extern char *craftPalRed KITTENS_CMD_ARGS;
extern char *craftPalSpread KITTENS_CMD_ARGS;
extern char *craftPalSwap KITTENS_CMD_ARGS;
extern char *craftPalSwapBank KITTENS_CMD_ARGS;
extern char *craftPalToBank KITTENS_CMD_ARGS;
extern char *craftReserveAsPalette KITTENS_CMD_ARGS;
extern char *craftRightTrimSTR KITTENS_CMD_ARGS;
extern char *craftSetAmosPri KITTENS_CMD_ARGS;
extern char *craftSetBankColour KITTENS_CMD_ARGS;
extern char *craftSetBlue KITTENS_CMD_ARGS;
extern char *craftSetComment KITTENS_CMD_ARGS;
extern char *craftSetGreen KITTENS_CMD_ARGS;
extern char *craftSetProtect KITTENS_CMD_ARGS;
extern char *craftSetRed KITTENS_CMD_ARGS;
extern char *craftSetWbPrefs KITTENS_CMD_ARGS;
extern char *craftStrCount KITTENS_CMD_ARGS;
extern char *craftStrPeekSTR KITTENS_CMD_ARGS;
extern char *craftStrPoke KITTENS_CMD_ARGS;
extern char *craftStrScrambleSTR KITTENS_CMD_ARGS;
extern char *craftStrUnscrambleSTR KITTENS_CMD_ARGS;
extern char *craftSysRequest KITTENS_CMD_ARGS;
extern char *craftTrAngle KITTENS_CMD_ARGS;
extern char *craftTrBack KITTENS_CMD_ARGS;
extern char *craftTrBase KITTENS_CMD_ARGS;
extern char *craftTrDistance KITTENS_CMD_ARGS;
extern char *craftTrDraw KITTENS_CMD_ARGS;
extern char *craftTrDrawRel KITTENS_CMD_ARGS;
extern char *craftTrError KITTENS_CMD_ARGS;
extern char *craftTrExec KITTENS_CMD_ARGS;
extern char *craftTrForw KITTENS_CMD_ARGS;
extern char *craftTrForward KITTENS_CMD_ARGS;
extern char *craftTrGetAngle KITTENS_CMD_ARGS;
extern char *craftTrHome KITTENS_CMD_ARGS;
extern char *craftTrLeft KITTENS_CMD_ARGS;
extern char *craftTrMemorizeA KITTENS_CMD_ARGS;
extern char *craftTrMemorizeX KITTENS_CMD_ARGS;
extern char *craftTrMemorizeY KITTENS_CMD_ARGS;
extern char *craftTrMove KITTENS_CMD_ARGS;
extern char *craftTrMoveRel KITTENS_CMD_ARGS;
extern char *craftTrPenDown KITTENS_CMD_ARGS;
extern char *craftTrPenState KITTENS_CMD_ARGS;
extern char *craftTrPenUp KITTENS_CMD_ARGS;
extern char *craftTrProportions KITTENS_CMD_ARGS;
extern char *craftTrRememberA KITTENS_CMD_ARGS;
extern char *craftTrRememberX KITTENS_CMD_ARGS;
extern char *craftTrRememberY KITTENS_CMD_ARGS;
extern char *craftTrReset KITTENS_CMD_ARGS;
extern char *craftTrRight KITTENS_CMD_ARGS;
extern char *craftTrSetHome KITTENS_CMD_ARGS;
extern char *craftTrTowards KITTENS_CMD_ARGS;
extern char *craftTrXHome KITTENS_CMD_ARGS;
extern char *craftTrXPos KITTENS_CMD_ARGS;
extern char *craftTrYHome KITTENS_CMD_ARGS;
extern char *craftTrYPos KITTENS_CMD_ARGS;
extern char *craftUpCaseSTR KITTENS_CMD_ARGS;
extern char *craftW_swap KITTENS_CMD_ARGS;
extern char *craftWarmReset KITTENS_CMD_ARGS;
extern char *craftWbDefPrefs KITTENS_CMD_ARGS;
extern char *craftWbPrefs KITTENS_CMD_ARGS;
extern char *craftWbToBack KITTENS_CMD_ARGS;
extern char *craftWbToFront KITTENS_CMD_ARGS;
extern char *craftYBeam KITTENS_CMD_ARGS;
