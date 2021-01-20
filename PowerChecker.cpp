// PowerChecker.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//
#include <stdio.h>
#include <windows.h>
#include <tchar.h>
#include <conio.h>

#pragma comment(lib, "winmm.lib" )

#define ESC 27

int c;
SYSTEM_POWER_STATUS sps;

void firstcheck(void) {
	GetSystemPowerStatus(&sps);															//システムの電源状態を取得
	if (sps.ACLineStatus == AC_LINE_OFFLINE)											//バッテリー駆動時
	{
		printf("監視を開始するには，まずAC電源を接続してください．自動で終了します．\nError Code 1.");
		Sleep(5000);																	//5秒待機する
		exit(1);																		//コード1を返し、終了
	}

	if (sps.ACLineStatus == AC_LINE_ONLINE)												//コンセント接続時
	{
		printf("監視を開始しました．\n監視を終了するにはESCキーを押してください．\n\n");
	}
}

void docheck(void) {
	GetSystemPowerStatus(&sps);															//システムの電源状態を取得
	if (sps.ACLineStatus == AC_LINE_OFFLINE)											//バッテリー駆動時
	{
		printf("警告!!\n");
		c = 0;																			//cに0を代入
		PlaySound(_TEXT("Alert.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);	//警告音を鳴らす
	}
	if (sps.ACLineStatus == AC_LINE_ONLINE)												//コンセント接続時
	{
		printf("正常\n");
		c = 1;																			//cに1を代入
	}
	Sleep(1000);

}

void managetime(void) {
	static int i = 0;
	static int m = 0;
	static int h = 0;

	if (i == 60)
	{
		m++;													//60秒になったら1分増やす
		i = 0;													//0秒に戻す
	}
	if (m == 60)
	{
		h++;													//60分になったら1時間増やす
		m = 0;													//0分に戻す
	}
	if (m == 0 && h == 0) printf("監視中...(%02ds)\n", i);		//0分かつ0時間のとき、秒数のみ表示
	if (m != 0 && h == 0) printf("監視中...(%02dm%02ds)\n", m, i);	//0時間で0分でないとき、分と秒数を表示
	if (h != 0) printf("監視中...(%02dh%02dm%02ds)\n", h, m, i);		//0時間でないとき、時間と分と秒数を表示
	i++;														//1秒増やす
}

int main(void) {

	printf("AC電源接続監視ツールv1.0.5 (c) Daichi Shigechika 2019 - 2020.\n\n");
	firstcheck();
	while (1) {
	
		managetime();
		docheck();
		if (c == 1)
		{
			if (_kbhit() && _getch() == ESC) break;					//cが1ならば、ESCキーによる割り込み処理を実施可
		}
	}
	printf("\n監視を終了しました．\n自動で終了します．\n");
	Sleep(5000);													//5秒待機する
	return 0;

}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
