#include <Novice.h>
#include "Struct.h"
#include "Color.h"
#include "RandPlus.h"
const char kWindowTitle[] = "LC1A_20_ヒサイチ_コウキ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);
	srand((unsigned)time(NULL));

	Emitter fance{};//パーティクル発生元の情報

	fance.pos = { 640,360 };
	fance.radius = { 10,300 };

	const int kFanceParticleNum = 200;//パーティクルの数
	Particle fanceParticle[kFanceParticleNum]{};
	fanceParticle[0].lifeTime = 45;//パーティクルの表示時間
	for (int i = 0; i < kFanceParticleNum; i++)
	{
		fanceParticle[i].acceleration.x = 0.1f;//減速させるため
		fanceParticle[i].acceleration.y = 0.8f;
	}

	float particleBound = 0.5f;//バウンドの係数

	bool particleFlag = false;//スペースでパーティクル発生
	int particleTimerMax = 10;//発生持続時間
	int particleTimer = 0;


	float min = 1280;
	float max = 0;

	int timer = 0;

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///                                                            ///
		/// --------------------↓更新処理ここから-------------------- ///
		///                                                            ///

		//パーティクル発生範囲を変更
		if (keys[DIK_S])
		{
			fance.radius.y += 4;
		}
		if (keys[DIK_W])
		{
			fance.radius.y -= 4;
		}
		if (keys[DIK_D])
		{
			fance.radius.x += 4;
		}
		if (keys[DIK_A])
		{
			fance.radius.x -= 4;
		}
		if (fance.radius.x <= 0)
		{
			fance.radius.x = 1;
		}if (fance.radius.y <= 0)
		{
			fance.radius.y = 1;
		}

		if (keys[DIK_SPACE])//&&!preKeys[DIK_SPACE]
		{
			particleFlag = true;
		}


		if (timer % 1 == 0)
		{

			if (particleFlag)
			{
				//パーティクルの生成
				for (int i = 0; i < kFanceParticleNum; i++)
				{
					if (fanceParticle[i].currentTime == 0)
					{
						fanceParticle[i].pos = { fance.pos.x + fance.radius.x - GetRandPos(fance.radius).x,fance.pos.y + fance.radius.y - GetRandPos(fance.radius).y };

						fanceParticle[i].radius = (float)GetRandMinMax(5, 10);
						//fanceParticle[i].max = (float)GetRandMinMax(30, 80);
						fanceParticle[i].currentTime++;
						fanceParticle[i].color.color[0] = GetRandMinMax(000, 000);//赤
						fanceParticle[i].color.color[1] = GetRandMinMax(000, 150);//緑
						fanceParticle[i].color.color[2] = GetRandMinMax(150, 255);//青
						fanceParticle[i].color.color[3] = 255;//透明度
						fanceParticle[i].velocity.x = (float)GetRandMinMax(-3, 3);//左右のブレ
						fanceParticle[i].velocity.y = (float)GetRandMinMax(-10, -3);//どのくらい飛び上がるか
						fanceParticle[i].boundPoint = -fanceParticle[i].velocity.y;//バウンドの場所を代入。床を作るイメージ
						fanceParticle[i].raito = 0;

						//1フレでより多く出したい時
						if (i < kFanceParticleNum - 1)
						{
							fanceParticle[i + 1].pos = { fance.pos.x + fance.radius.x - GetRandPos(fance.radius).x,fance.pos.y + fance.radius.y - GetRandPos(fance.radius).y };

							fanceParticle[i + 1].radius = (float)GetRandMinMax(5, 10);
							//fanceParticle[i + 1].max = (float)GetRandMinMax(30, 80);
							fanceParticle[i + 1].currentTime++;
							fanceParticle[i + 1].color.color[0] = GetRandMinMax(000, 000);
							fanceParticle[i + 1].color.color[1] = GetRandMinMax(000, 150);
							fanceParticle[i + 1].color.color[2] = GetRandMinMax(150, 255);
							fanceParticle[i + 1].color.color[3] = 255;
							fanceParticle[i + 1].velocity.x = float(GetRandMinMax(-3, 3));
							fanceParticle[i + 1].velocity.y = (float)GetRandMinMax(-10, -3);
							fanceParticle[i + 1].boundPoint = -fanceParticle[i + 1].velocity.y;
							fanceParticle[i + 1].raito = 0;
						}
						break;
					}
				}

				if (particleTimer < particleTimerMax)
				{
					particleTimer++;
				}
				else
				{
					particleFlag = false;
					particleTimer = 0;
				}
			}
			//パーティクルの移動
			for (int i = 0; i < kFanceParticleNum; i++)
			{


				//パーティクルが生きてる時
				if (fanceParticle[i].currentTime != 0 && fanceParticle[i].currentTime < fanceParticle[0].lifeTime)
				{
					fanceParticle[i].currentTime++;

					//x軸の移動を徐々に減速
					if (fanceParticle[i].velocity.x >= 0.5f || fanceParticle[i].velocity.x <= -0.5f)
					{
						if (fanceParticle[i].velocity.x < 0)
						{
							fanceParticle[i].velocity.x += 0.1f;
						}
						if (fanceParticle[i].velocity.x > 0)
						{
							fanceParticle[i].velocity.x -= 0.1f;//fanceParticle[i].acceleration.x
						}
					}
					else
					{
						fanceParticle[i].velocity.x = 0;
					}


					//y軸の重力計算＆バウンド
					if (fanceParticle[i].velocity.y < 10)
					{
						fanceParticle[i].velocity.y += fanceParticle[i].acceleration.y;

					}
					if (fanceParticle[i].velocity.y > fanceParticle[i].boundPoint)
					{
						fanceParticle[i].velocity.y *= -particleBound;
						fanceParticle[i].boundPoint *= particleBound;
					}



					fanceParticle[i].pos.x += fanceParticle[i].velocity.x;
					//y軸の速度が0付近の時はポジションを動かさない。
					if (fanceParticle[i].velocity.y > 1 || fanceParticle[i].velocity.y < -1)fanceParticle[i].pos.y += fanceParticle[i].velocity.y;

					//色のグラデーションの変化の割合を計算
					if (fanceParticle[i].raito < 100)fanceParticle[i].raito += 100 / fanceParticle[0].lifeTime;

					//色

					//透明スタートなら使う。
					//if (fanceParticle[i].color.color[3] < 255)
					//{
					//	fanceParticle[i].color.color[3] += 10;
					//}
					//if (fanceParticle[i].color.color[3] > 255)
					//{
					//	fanceParticle[i].color.color[3] = 255;
					//}

					if (fanceParticle[i].pos.x <= min && fanceParticle[i].pos.x != 0)
					{
						min = fanceParticle[i].pos.x;
					}
					if (fanceParticle[i].pos.x >= max)
					{
						max = fanceParticle[i].pos.x;

					}
				}
				else
				{

					fanceParticle[i].currentTime = 0;
					fanceParticle[i].velocity = { 0,0 };
					fanceParticle[i].color.color[3] = 0;
				}
			}
		}
		timer++;
		///                                                            ///
		/// --------------------↑更新処理ここまで-------------------- ///
		///                                                            ///

		///                                                            ///
		/// --------------------↓描画処理ここから-------------------- ///
		///                                                            ///

		Novice::DrawBox(0, 0, 1280, 720, 0, 0x223344ff,kFillModeSolid);
		Novice::DrawBox(int(fance.pos.x - fance.radius.x), int(fance.pos.y - fance.radius.y), int(fance.radius.x * 2), int(fance.radius.y * 2), 0, WHITE, kFillModeWireFrame);

		Novice::SetBlendMode(kBlendModeAdd);
		for (int i = 0; i < kFanceParticleNum; i++)
		{
			Novice::DrawEllipse(int(fanceParticle[i].pos.x), int(fanceParticle[i].pos.y), int(fanceParticle[i].radius), int(fanceParticle[i].radius), 0, ColorGradation({ fanceParticle[i].color.color[0],fanceParticle[i].color.color[1],fanceParticle[i].color.color[2],fanceParticle[i].color.color[3] }, { 0xff,0xff,0xff,0x00 }, fanceParticle[i].raito, 100), kFillModeSolid);
		}

		Novice::SetBlendMode(kBlendModeNormal);


		////デバッグ用
		//Novice::ScreenPrintf(0, 0, "particleFlag=%d", particleFlag);

		//for (int i = 0; i < 30; i++)
		//{
		//	Novice::ScreenPrintf(0, 30 + i * 20, "fP[%d].vel.x=%f", i, fanceParticle[i].velocity.x);

		//	if (fanceParticle[i].velocity.x > 0)
		//	{
		//		Novice::DrawBox(0, 30 + i * 20, 100, 20, 0, RED, kFillModeSolid);
		//	}
		//	else if (fanceParticle[i].velocity.x < 0)
		//	{
		//		Novice::DrawBox(0, 30 + i * 20, 100, 20, 0, BLUE, kFillModeSolid);
		//	}
		//	else if (fanceParticle[i].velocity.x == 0)
		//	{
		//		Novice::DrawBox(0, 30 + i * 20, 100, 20, 0, 0xaaaa00ff, kFillModeSolid);

		//	}
		//}
		//Novice::DrawLine(int(min), 0, int(min), 720, BLUE);
		//Novice::DrawLine(int(max), 0, int(max), 720, RED);

		//Novice::ScreenPrintf(200, 0, "min=%f max=%f", 640 - min, 640 - max);
		//Novice::ScreenPrintf(600, 0, ">>SPACE<<");
		///                                                            ///
		/// --------------------↑描画処理ここまで-------------------- ///
		///                                                            ///


		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
