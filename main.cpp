#include <Novice.h>
#include "Struct.h"
#include "Color.h"
#include "RandPlus.h"
#include "ImGuiManager.h"
#include "DrawPlus.h"
const char kWindowTitle[] = "LC1A_20_ヒサイチ_コウキ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);
	srand((unsigned)time(NULL));

	Emitter fance{};//パーティクル発生元の情報

	fance.pos = { 640,360 };//出現場所の中心
	fance.radius = { 10,300 };//半径
	fance.particleSpawnFlag = false; //スペースでパーティクル発生
	fance.particleTimerMax = 10;//発生持続時間を設定
	fance.particleBound = 0.5f;//バウンドの係数
	fance.spownCount = 2;//一度に出る数

	const int kFanceParticleNum = 200;//パーティクルの数
	Particle fanceParticle[kFanceParticleNum]{};//パーティクルの情報
	fanceParticle[0].lifeTime = 45;//パーティクルの表示時間
	for (int i = 0; i < kFanceParticleNum; i++)
	{
		fanceParticle[i].acceleration.x = 0.1f;//減速させるため
		fanceParticle[i].acceleration.y = 0.8f;
	}

	//float particleBound = 0.5f;//バウンドの係数

	//bool particleFlag = false;//スペースでパーティクル発生
	//int particleTimerMax = 10;//発生持続時間を設定
	//int particleTimer = 0;//発生持続時間をカウント


	int whiteTexture = Novice::LoadTexture("white1x1.png");

	int jumpMin = 3;
	int jumpMax = 10;
	int rolling = 3;

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

		//範囲が0以下にならないように
		if (fance.radius.x <= 0)
		{
			fance.radius.x = 1;
		}if (fance.radius.y <= 0)
		{
			fance.radius.y = 1;
		}



		if (keys[DIK_SPACE] && !preKeys[DIK_SPACE])//&&!preKeys[DIK_SPACE]
		{
			//パーティクル生成フラグを立てる
			fance.particleSpawnFlag = true;
		}



		if (fance.particleSpawnFlag)
		{
			//パーティクルの生成

			for (int j = 0; j < fance.spownCount; j++)
			{
				for (int i = 0; i < kFanceParticleNum; i++)
				{
					if (fanceParticle[i].currentTime == 0)
					{

						//fanceの場所からfanceの半径を引いた矩形の範囲にランダムな場所で生成
						fanceParticle[i].pos = { fance.pos.x - fance.radius.x + GetRandPos(fance.radius).x,fance.pos.y - fance.radius.y + GetRandPos(fance.radius).y };

						fanceParticle[i].radius = (float)GetRandMinMax(5, 10);
						fanceParticle[i].currentTime++;//0だともう一度生成されるので、時間を進める
						fanceParticle[i].color.color[0] = GetRandMinMax(000, 000);//赤
						fanceParticle[i].color.color[1] = GetRandMinMax(000, 150);//緑
						fanceParticle[i].color.color[2] = GetRandMinMax(150, 255);//青
						fanceParticle[i].color.color[3] = 255;//透明度
						fanceParticle[i].velocity.x = (float)GetRandMinMax(-rolling, rolling);//左右のブレ
						fanceParticle[i].velocity.y = (float)GetRandMinMax(-jumpMax, -jumpMin);//どのくらい飛び上がるか
						fanceParticle[i].boundPoint = fanceParticle[i].pos.y;//バウンドの場所を代入。床を作るイメージ
						fanceParticle[i].raito = 0;//0~100%の割合を初期化

						////1フレでより多く出したい時
						//if (i < kFanceParticleNum - 1)
						//{
						//	fanceParticle[i + 1].pos = { fance.pos.x - fance.radius.x + GetRandPos(fance.radius).x,fance.pos.y - fance.radius.y + GetRandPos(fance.radius).y };

						//	fanceParticle[i + 1].radius = (float)GetRandMinMax(5, 10);
						//	fanceParticle[i + 1].currentTime++;
						//	fanceParticle[i + 1].color.color[0] = GetRandMinMax(000, 000);
						//	fanceParticle[i + 1].color.color[1] = GetRandMinMax(000, 150);
						//	fanceParticle[i + 1].color.color[2] = GetRandMinMax(150, 255);
						//	fanceParticle[i + 1].color.color[3] = 255;
						//	fanceParticle[i + 1].velocity.x = float(GetRandMinMax(-3, 3));
						//	fanceParticle[i + 1].velocity.y = (float)GetRandMinMax(-10, -3);
						//	fanceParticle[i + 1].boundPoint = -fanceParticle[i + 1].velocity.y;
						//	fanceParticle[i + 1].raito = 0;
						//}
						break;
					}
				}
			}
			

			if (fance.particleTimerCount < fance.particleTimerMax)
			{
				fance.particleTimerCount++;//パーティクル出現時間を進める
			}
			else
			{
				//パーティクル出現時間が指定した値を超えたら生成をやめる
				fance.particleSpawnFlag = false;
				fance.particleTimerCount = 0;
			}
		}
		//パーティクルの移動
		for (int i = 0; i < kFanceParticleNum; i++)
		{


			//パーティクルが生きてる時
			if (fanceParticle[i].currentTime != 0 && fanceParticle[i].currentTime < fanceParticle[0].lifeTime)
			{
				fanceParticle[i].currentTime++;//時間を進めていく

				//x軸の移動を徐々に減速
				//velocityが-0.5~0.5の範囲になったら速度を0にする(減速をやめる)
				if (fanceParticle[i].velocity.x >= 0.1f || fanceParticle[i].velocity.x <= -0.1f)
				{
					if (fanceParticle[i].velocity.x < 0)
					{
						fanceParticle[i].velocity.x += fanceParticle[0].acceleration.x;
					}
					if (fanceParticle[i].velocity.x > 0)
					{
						fanceParticle[i].velocity.x -= fanceParticle[0].acceleration.x;//fanceParticle[i].acceleration.x
					}
				}
				else
				{
					fanceParticle[i].velocity.x = 0;
				}


				//y軸の重力計算＆バウンド
				if (fanceParticle[i].velocity.y < 10)
				{
					//重力を計算
					fanceParticle[i].velocity.y += fanceParticle[0].acceleration.y;

				}
				


				//ポジションの移動
				fanceParticle[i].pos.x += fanceParticle[i].velocity.x;
				//y軸の速度が0付近の時はポジションを動かさない。
				if (fanceParticle[i].velocity.y > 1 || fanceParticle[i].velocity.y < -1)fanceParticle[i].pos.y += fanceParticle[i].velocity.y;


				//velocityがバウンドの値(仮想の床に当たったら)
				if (fanceParticle[i].pos.y >= fanceParticle[i].boundPoint)
				{
					//y軸のvelocityを反転&減速して、仮想床の値を更新
					fanceParticle[i].velocity.y *= -fance.particleBound;
					//fanceParticle[i].boundPoint *= fance.particleBound;
				}

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


			}
			else
			{
				//初期化して生成出来るように
				fanceParticle[i].currentTime = 0;
				fanceParticle[i].velocity = { 0,0 };
				fanceParticle[i].color.color[3] = 0;
			}
		}


		///                                                            ///
		/// --------------------↑更新処理ここまで-------------------- ///
		///                                                            ///

		///                                                            ///
		/// --------------------↓描画処理ここから-------------------- ///
		///                                                            ///

		Novice::DrawBox(0, 0, 1280, 720, 0, 0x223344ff, kFillModeSolid);
		//デバッグ用　fanceの範囲(emitter)を可視化
		Novice::DrawBox(int(fance.pos.x - fance.radius.x), int(fance.pos.y - fance.radius.y), int(fance.radius.x * 2), int(fance.radius.y * 2), 0, WHITE, kFillModeWireFrame);

		Novice::SetBlendMode(kBlendModeNormal);
		for (int i = 0; i < kFanceParticleNum; i++)
		{
			//雑に円で描画してる
			//Novice::DrawEllipse(int(fanceParticle[i].pos.x), int(fanceParticle[i].pos.y), int(fanceParticle[i].radius), int(fanceParticle[i].radius), 0, ColorGradation({ fanceParticle[i].color.color[0],fanceParticle[i].color.color[1],fanceParticle[i].color.color[2],fanceParticle[i].color.color[3] }, { 0xff,0xff,0xff,0x00 }, fanceParticle[i].raito, 100), kFillModeSolid);
			DrawQuadAlpha(
				fanceParticle[i].pos,
				{ fanceParticle[i].radius,
				fanceParticle[i].radius },
				{ 1,1 },
				-fanceParticle[i].velocity.x,
				{0,0},
				{1,1},
				whiteTexture,
				ColorGradation(
					{ fanceParticle[i].color.color[0],fanceParticle[i].color.color[1],fanceParticle[i].color.color[2],fanceParticle[i].color.color[3] }, 
					{ 0xff,0xff,0xff,0x00 }, 
					fanceParticle[i].raito, 100));

		}

		Novice::SetBlendMode(kBlendModeNormal);


		ImGui::Begin("test");
		ImGui::SliderFloat("fance.pos.x", &fance.pos.x, 0, 1280);
		ImGui::SliderFloat("fance.pos.y", &fance.pos.y, 0, 720);
		ImGui::SliderFloat("fance.radius.x", &fance.radius.x, 1, 1000);
		ImGui::SliderFloat("fance.radius.y", &fance.radius.y, 1, 1000);
		ImGui::SliderFloat("fance.particleBound", &fance.particleBound, 0, 1.0f);
		ImGui::SliderFloat("lifeTime", &fanceParticle[0].lifeTime, 1, 200);
		ImGui::SliderFloat("fanceParticle[0].acceleration.x", &fanceParticle[0].acceleration.x,0, 1.0f);
		ImGui::SliderFloat("fanceParticle[0].acceleration.y", &fanceParticle[0].acceleration.y,0, 2.0f);
		ImGui::SliderInt("fance.spownCount", &fance.spownCount, 1, 100);
		ImGui::SliderInt("rolling", &rolling, 0, 50);
		ImGui::SliderInt("jumpMin", &jumpMin, 0, 50);
		ImGui::SliderInt("jumpMax", &jumpMax, 0, 50);

		ImGui::End();

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
