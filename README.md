# はじめに

このリポジトリは、GNU Multi-Precision Library（GMP）を使用した素因数分解の試行を行うリポジトリです。

ほぼ私の勉強のためのリポジトリに近いです。

# GMPについて

GMPとは多倍長演算をC/C++で行うことを想定したライブラリです。
私は主にCで使用していますが、C++だとboostのラップがかかったGMPを使用している人が多い印象を受けます。
私もC++で使用する場合はboostを経由させて使用しています。

詳しくはWikipediaを参照。

https://ja.wikipedia.org/wiki/GNU_Multi-Precision_Library

GMPはシングルスレッドで最適化されており、最速を目指しているそうです。

GPUとか使って自前で使用したら、GMPの方が遅いこともあると思いますが、そうでない場合は圧倒的にGMPは速いです。

よって、一般的には多倍長演算を自前で実装するよりも、GMPを使用して実装した方が効率良く実装できます。

RSAの実装に使用する数論関数、その他、多倍長演算のビット演算子もサポートしています。


# factorizationパッケージ関連

## factorコマンド

Linuxで実行できるfactorコマンド：

以下のコマンドで実行できます。

```
factor [input]
```
ソースは以下：

https://github.com/coreutils/coreutils/blob/master/src/factor.c

コメント文から以下を抜粋

```
Algorithm:
    (1) Perform trial division using a small primes table, but without hardware
        division since the primes table store inverses modulo the word base.
        (The GMP variant of this code doesn't make use of the precomputed
        inverses, but instead relies on GMP for fast divisibility testing.)
    (2) Check the nature of any non-factored part using Miller-Rabin for
        detecting composites, and Lucas for detecting primes.
    (3) Factor any remaining composite part using the Pollard-Brent rho
        algorithm or if USE_SQUFOF is defined to 1, try that first.
        Status of found factors are checked again using Miller-Rabin and Lucas.
    We prefer using Hensel norm in the divisions, not the more familiar
    Euclidian norm, since the former leads to much faster code.  In the
    Pollard-Brent rho code and the prime testing code, we use Montgomery's
    trick of multiplying all n-residues by the word base, allowing cheap Hensel
    reductions mod n.
    The GMP code uses an algorithm that can be considerably slower;
    for example, on a circa-2017 Intel Xeon Silver 4116, factoring
    2^{127}-3 takes about 50 ms with the two-word algorithm but would
    take about 750 ms with the GMP code.
```
一応、これも上記アルゴリズムを見た感じだとGMPベースな感じを受けます。
実際ヘッダファイルにもGMPのヘッダ（gmp.h）がインクルードされているし、GMPの関数もコールされているので、間違いないと思われます。
ただ、コメントを見る感じ、GMPなしでも動作するように改良が加えられているようです。（詳しくはわからない）

## ECMパッケージ

楕円曲線法のパッケージ

https://stdkmd.net/nrr/ecm_ja.htm

GMPベースの実装


## Msieveパッケージ

楕円曲線法、数体ふるい法など

http://inaz2.hatenablog.com/entry/2016/01/09/032521

GMPを使用して実装されています。

## GGNFSパッケージ

一般数体ふるい法を使用している。

https://stdkmd.net/nrr/ggnfs_ja.htm

Msieveの方が個人的には使いやすいと思っています。

こちらもGMPを使用しているようです。

# ウェブサービス関連

素因数分解してくれるウェブサービス、ただし試し割りをしている感覚に近い。

http://factordb.com/

# プログラム

ポラードのロー法とフェルマの平方差分法は簡単に実装でき、かつロー法は優秀。

フェルマの平方差分法は2次ふるい法などのアプローチにも応用されているので、勉強するにはここから。

## 事前準備

GMPのパッケージとbcのインストール

```
sudo apt install -y libgmp-dev bc
```

コンパイル

```
make
```

ポラードのロー法の実行

```
echo "31*11" | bc | ./rho
```

# 参考

factorizationのアルゴリズムが色々のってて楽しい

https://wacchoz.hatenablog.com/entry/2019/01/20/120000

http://fussy.web.fc2.com/algo/math11_factorization1.htm
