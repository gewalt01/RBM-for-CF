﻿/**
*	@file GBRBMCFTrain.h
*	@brief GBRBMCFの訓練クラス
*/
#pragma once
#include "GBRBMCF.h"
#include "GBRBMDatasetContainer.h"

/**
	@class GBRBMCFTrain
	@brief GBRBMCFを学習させるクラス
*/
class GBRBMCFTrain
{

public:
	/**
		@brief コンストラクタ
		@param vlen 可視変数の数
		@param hlen 隠れ変数の数
		@param epoch 学習の反復回数
		@param learning_rate 学習率
	*/
	GBRBMCFTrain(unsigned int vlen, unsigned int hlen, unsigned int epoch, double leaning_rate);

	/**
		@brief コンストラクタ
		@param vlen 可視変数の数
		@param hlen 隠れ変数の数
		@param epoch 学習の反復回数
		@param learning_rate 学習率
		@param cdk Contrastive Divergenceの反復回数
	*/
	GBRBMCFTrain(unsigned int vlen, unsigned int hlen, unsigned int epoch, double leaning_rate, unsigned int cdk);

	/**
		@brief デストラクタ
	*/
	~GBRBMCFTrain();

	/**
		@brief データごとに学習(データを捨てていないのでオンライン学習かどうかは微妙)
		@param rbm rbmオブジェクト
		@param 観測データセット
		@return 成功したらtrue, 失敗でfalse.
	*/
	bool train(GBRBMCF & rbm, GBRBMDatasetContainer & datasets);

	/**
		@brief 全データで学習(バッチ学習, 全データに対する勾配を計算)
		@param rbm rbmオブジェクト
		@param 観測データセット
		@return 成功したらtrue, 失敗でfalse.
	*/
	bool trainBatch(GBRBMCF & rbm, GBRBMDatasetContainer & datasets);


private:
	unsigned int epoch; /** 学習の反復回数 */
	double learningRate; /** 学習率 */
	unsigned int vlength; /** 可視変数の数 */
	unsigned int hlength; /**  隠れ変数の数 */
	unsigned int cdk = 1; /** Contrastive Divergenceの反復回数 */
	std::vector<double> _tmpGradientVbias; /** 最後に計算した可視変数パラメータの勾配 */
	std::vector<double> _tmpGradientVariance; /** 最後に計算した隠れ変数パラメータの勾配 */
	std::vector<double> _tmpGradientHbias; /** 最後に計算した重みパラメータの勾配 */
	std::vector< std::vector<double> > _tmpGradientWeight; /** 最後に計算した可視変数分散パラメータの勾配 */
	std::vector<unsigned int> _table; /** 既知データ一覧 */

	/**
		@brief データ1つからの勾配を計算 内部処理なのでプライベート関数へ移行予定
		@param rbm rbmオブジェクト
		@param dataset 観測データ
		@return 成功したらtrue, 失敗でfalse.
	*/
	bool _getGradient(GBRBMCF & rbm, GBRBMDataset & dataset);

	/**
		@brief Contrastive Divergence 内部処理なのでプライベート関数へ移行予定
		@param rbm rbmオブジェクト
		@param cdk Contrastive Divergenceの反復回数
		@return 成功したらtrue, 失敗でfalse.
	*/
	bool contrastiveDivergence(GBRBM *rbm, unsigned int cdk);
};

