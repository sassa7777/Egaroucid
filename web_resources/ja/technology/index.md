# Egaroucid 技術資料



## 技術解説

日本語のみでEgaroucidの[技術解説](./explanation)を書きました。のんびりと追記します。



## ベンチマーク

Egaroucidの性能の確認として2種類のベンチマークを使用しています。1つ目は[The FFO endgame test suite](http://www.radagast.se/othello/ffotest.html)です。これは、終盤の完全読みにかかる時間に関するベンチマークです。2つ目は対戦です。Egaroucidの過去バージョンの他、他の強豪オセロAIとの対戦として、[Edax 4.4](https://github.com/abulmo/edax-reversi/releases/tag/v4.4)とも対戦しました。単純に評価関数の強さを計測するため、bookを使わず、[XOT](https://berg.earthlingz.de/xot/aboutxot.php?lang=en)という初期局面集を用いて対戦させました。

### The FFO endgame test suite

終盤探索は、以下3つの指標で評価しています。

<ul>
    <li>計算時間</li>
    <li>訪問ノード数</li>
    <li>NPS (1秒あたりのノード訪問回数)</li>
</ul>

ユーザにとって一番重要なのは計算時間です。決まったテストケースを処理するのにかかる時間を秒数で表します。ここでは[The FFO endgame test suite](http://www.radagast.se/othello/ffotest.html)の40から59番のテストケース(20から34手完全読み)にかかる時間を使いました。これは減ると嬉しい値です。

計算時間を短くするには、まず(厳密に)無駄な探索を減らせば良いです。無駄な探索が多いと訪問ノード数(探索した盤面の数)が増えます。これも減ると嬉しい値です。

計算時間を短くするためのもう一つの観点は、1秒あたりのノード訪問回数を上げることです。これはNodes Per Secondの頭文字を取ってNPSと言われます。これは上がると嬉しい値です。

以下はThe FFO endgame test suiteの40から59番をCore i9 13900Kで実行した結果を、バージョンを横軸に取ってグラフにしたものです。SIMD版を使用しました。

<div class="centering_box">
	<img class="pic2" src="img/ffo_time.png">
    <img class="pic2" src="img/ffo_node.png">
    <img class="pic2" src="img/ffo_nps.png">
</div>
バージョン7.4.0は7.3.0よりも計算時間が多くかかっていますが、これはIntelマイクロコード0x129による性能低下に起因するものです。7.3.0のベンチマーク測定時には0x129適用前でしたが、7.4.0測定時には0x129適用済みでした。

### XOTによる対戦

オセロAIの強さを評価するためには、対戦するのが一番でしょう。ここでは、各バージョンに[Edax 4.6](https://github.com/abulmo/edax-reversi/releases/tag/v4.6)を加え、総当たり戦をした結果を掲載します。

対戦はレベル1(中盤1手読み、終盤2手完全読み)およびレベル5(中盤5手読み、終盤10手完全読み)で行いました。

対戦にはそれぞれ[XOT](https://berg.earthlingz.de/xot/aboutxot.php?lang=en)の進行を初期盤面として使い、各進行では先手後手それぞれ1回ずつ対戦させています。

<div class="table_wrapper"><table>
<tr><th>名称</th><td>7.6.0</td><td>7.5.0</td><td>7.4.0</td><td>7.3.0</td><td>7.2.0</td><td>7.1.0</td><td>7.0.0</td><td>Edax4.6</td></tr><tr><th>レベル1 勝率</th><td>0.5711</td><td>0.5514</td><td>0.5354</td><td>0.5289</td><td>0.5049</td><td>0.4943</td><td>0.5366</td><td>0.2774</td></tr><tr><th>レベル1 平均獲得石数</th><td>+3.36</td><td>+2.10</td><td>+1.59</td><td>+1.21</td><td>+0.44</td><td>+0.08</td><td>+1.41</td><td>-10.19</td></tr><tr><th>レベル5 勝率</th><td>0.6151</td><td>0.5580</td><td>0.5291</td><td>0.5154</td><td>0.5211</td><td>0.5260</td><td>0.5011</td><td>0.2340</td></tr><tr><th>レベル5 平均獲得石数</th><td>+2.51</td><td>+1.63</td><td>+1.15</td><td>+0.49</td><td>+0.52</td><td>+0.92</td><td>+0.11</td><td>-7.33</td></tr>
</table></div>

対戦の詳細は[こちら](./battle.txt)をご覧ください。



### バージョンごとの詳細

各バージョンのベンチマークを公開します。上で載せなかった古いバージョンのベンチマークもあります。

こちらの詳細はバージョンごとに少し条件が違うものもありますので、詳細はそれぞれのページをご覧ください。

<div class="table_wrapper"><table>
<tr><th>バージョン</th><td><a href="./benchmarks/7_6_0/">7.6.0</a></td><td><a href="./benchmarks/7_5_0/">7.5.0</a></td><td><a href="./benchmarks/7_4_0/">7.4.0</a></td><td><a href="./benchmarks/7_3_0/">7.3.0</a></td><td><a href="./benchmarks/7_2_0/">7.2.0</a></td><td><a href="./benchmarks/7_1_0/">7.1.0</a></td><td><a href="./benchmarks/7_0_0/">7.0.0</a></td><td><a href="./benchmarks/6_5_0/">6.5.0</a></td><td><a href="./benchmarks/6_4_0/">6.4.0</a></td><td><a href="./benchmarks/6_3_0/">6.3.0</a></td><td><a href="./benchmarks/6_2_0/">6.2.0</a></td><td><a href="./benchmarks/6_1_0/">6.1.0</a></td><td><a href="./benchmarks/6_0_0/">6.0.0</a></td><td><a href="./benchmarks/5_10_0/">5.10.0</a></td><td><a href="./benchmarks/5_9_0/">5.9.0</a></td><td><a href="./benchmarks/5_8_0/">5.8.0</a></td><td><a href="./benchmarks/5_7_0/">5.7.0</a></td><td><a href="./benchmarks/5_5_0/">5.5.0/5.6.0</a></td><td><a href="./benchmarks/5_4_1/">5.4.1</a></td></tr><tr><th>リリース日</th><td>2025/04/02</td><td>2024/12/24</td><td>2024/10/03</td><td>2024/08/16</td><td>2024/06/25</td><td>2024/06/06</td><td>2024/04/17</td><td>2023/10/25</td><td>2023/09/01</td><td>2023/07/09</td><td>2023/03/15</td><td>2022/12/23</td><td>2022/10/10</td><td>2022/06/08</td><td>2022/06/07</td><td>2022/05/13</td><td>2022/03/26</td><td>2022/03/16</td><td>2022/03/02</td></tr>
</table></div>




## 学習データ公開

Egaroucidで生成した、オセロAI向け学習データを大量に公開しています。詳しくは[学習データ](./train-data)をご覧ください。

