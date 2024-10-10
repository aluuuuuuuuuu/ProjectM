#pragma once
class StageManager
{
public:
	StageManager();
	virtual ~StageManager();

	/// <summary>
	/// ステージを描画する
	/// </summary>
	void DrawStage() const;

    /// <summary>
    /// ステージの配列の中身を取得する
    /// </summary>
    /// <param name="a">配列のx要素</param>
    /// <param name="b">配列のy要素</param>
    /// <param name="c">配列のz要素</param>
    /// <returns>配列の要素</returns>
    int GetStageInfo(int a, int b, int c);

private:



    int _stage[10][2][10];
};

