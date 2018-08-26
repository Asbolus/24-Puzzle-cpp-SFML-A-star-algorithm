# 24-Puzzle cpp SFML with A* algorithm

------
**The 24-Puzzle game  practice in C++ and SFML**<br>
**Code reference from FamTrinli's YouTube channel**
**Whole program architecture idea reference from Chuan-Jie Lin**

[YouTube video link](http://www.youtube.com/watch?v=LPXi9uIxKpQ)<br>
[![](http://img.youtube.com/vi/LPXi9uIxKpQ/0.jpg)](http://www.youtube.com/watch?v=LPXi9uIxKpQ "24-Puzzle")

I have poor English ability so I can't describe clearly and there may some grammar/word mistakes. My native language is Chinese so I will write down both English and Chinese.<br>
I am a beginner, please give me some suggestions to improve my coding ability. English advice also. :)

Descriptions:
------
The game looks like below. And your goal is slide the puzzle to orderly.<br>

 2|24| 8| 5| 4
---|---|---|---|---
15| t|23|10| 9
20| 7|14|12| 3
 6|11|18|21|17
16| 1|22|13|19


<br>
|&nbsp;| 1| 2| 3| 4|
|:--:|:--:|:--:|:--:|:--:|
| 5| 6| 7| 8| 9|
|10|11|12|13|14|
|15|16|17|18|19|
|20|21|22|23|24|
<br>
More details about the N-puzzle game, you can see [Wiki](https://en.wikipedia.org/wiki/15_puzzle)
This program running looks like below. The path show right is using [A* algorithm](https://en.wikipedia.org/wiki/A*_search_algorithm) to find the shortest path, there is 4 parts to build the system.<br>
![GamePNG](https://i.imgur.com/lqrRdno.png)

<font size=4>**Program properties**</font>
|Property	|Variable	|Type|	Description|
|:--|:--:|:--:|:--|
|State represntation| stateRps| string| A 25-character string, a permutation of "0ABCDEFGHIJKLMNOPQRSTUVWX"|
|Action Sequence| actionSeqence| string| A sequence of actions to change the initial state into this state|
|Spent cost|	cost_g|	integer|	Cost (steps) already spent from the initial state to this state|
|Estimated future cost(Heuristic value)|	cost_h|	integer|	Estimated cost (steps) from this state to the goal state|
|Total cost| cost_f |integer |cost_f = cost_g + cost_h|
<br>
<font size=4>**Part I: Solvability decision**</font>
It's no need to do because the puzzle **absolute** have solution. Depend on the puzzle  is slide the orderly puzzle randomly.<br>

<font size=4>**Part II:  Manhattan distance**</font>
See [Manhattan distance](https://en.wikipedia.org/wiki/Taxicab_geometry)
Steps:

1. Convert a state into a *n* × *n* matrix; remember the (x<sub>i</sub>, y<sub>i</sub>) coordination of each digit i
2. Also convert the goal state into a *n* × *n* matrix and remember the (a<sub>i</sub>, b<sub>i</sub>) coordination of each digit i
3. The Manhattan distance is Σ<sub>i</sub> | x<sub>i</sub> - a<sub>i</sub> | + | y<sub>i</sub> - b<sub>i</sub> |

Current state<br>
| 7| 2| 4|
|:--:|:--:|:--:|
| 5|  | 6|
| 8| 3| 1|
<br>
Goal state<br>
|&nbsp;| 1| 2|
|:--:|:--:|:--:|
| 3| 4| 5|
| 6| 7| 8|
<br>
| Digit| Current position| Goal position|     Manhattan distance      |
|:----:|:---------------:|:------------:|:---------------------------:|
|     1|      (2,2)      |     (0,1)    |\|2-0\| + \|2-1\| = 2 + 1 = 3|
|     2|      (0,1)      |     (0,2)    |\|0-0\| + \|1-2\| = 0 + 1 = 1|
|     3|      (2,1)      |     (1,0)    |\|2-1\| + \|1-0\| = 1 + 1 = 2|
|     4|      (0,2)      |     (1,1)    |\|0-1\| + \|2-1\| = 1 + 1 = 2|
|     5|      (1,0)      |     (1,2)    |\|1-1\| + \|0-2\| = 0 + 2 = 2|
|     6|      (1,2)      |     (2,0)    |\|1-2\| + \|2-0\| = 1 + 2 = 3|
|     7|      (0,0)      |     (2,1)    |\|0-2\| + \|0-1\| = 2 + 1 = 3|
|     8|      (2,0)      |     (2,2)    |\|2-2\| + \|0-2\| = 0 + 2 = 2|
<br>
Sum of Manhattan distances: 18<br>

<font size=4>**Part III: Successor function**</font>
Input: a state = (stateRps, lastCostOfG, lastActionSequence)<br>
Steps:
1. Convert a state into an *n* × *n* matrix
2. Find the coordination of digit 0 as (x<sub>0</sub>, y<sub>0</sub>)
3. Swap 0 with the digits in (x<sub>0</sub>, y<sub>0</sub>-1), (x<sub>0</sub>, y<sub>0</sub>+1), (x<sub>0</sub>-1, y<sub>0</sub>), (x<sub>0</sub>+1, y<sub>0</sub>) if they are legal actions

<font size=4>**Part IV: Priority queue**</font>
Step:
1. Use STL container [priority_queue](http://www.cplusplus.com/reference/queue/priority_queue/) is a easy way to implement priority queue
2. Create a compare struct cmp for priority queue
3. Push legal actions from Successor function into priority queue
4. Pop the priority queue, the top is the smallest cost action
5. Call Successor function again where input is the object which just pop, repeat until solve the puzzle


<font size=4>**Additional**</font>
If you want to know the puzzle is solvable or not,  check the board of a N-puzzle game is *n* x *n* square where N = *n* x *n* - 1.<br>
If *n* is odd, and the number of disorder digits is even, the problem is solvable.<br>
| 3| 1| 2|
|:--:|:--:|:--:|
| 4| 5| 7|
| 6| 8|  |
<br>
is unsolvable, because its state representation 31245768 (discarding 0) has 3 disordered pairs: (1,3) (2,3) (6,7).<br><br>

If *n* is even, and the index of the row containing the epmty tile plus the number of disorder digits is even, the problem is solvable.<br>
| 1| 2| 7| 4|
|:--:|:--:|:--:|:--:|
| 3|  | 6|10|
| 8| 5|13| 1|
| 9|12|14|15|
<br>
is unsolvable,<br>
because its state representation 127436A85DB9CEF (discarding 0) has 14 disordered pairs: (3,7) (4,7) (5,7) (6,7) (3,4) (5,6) (5,A) (8,A) (9,A) (5,8) (9,D) (B,D) (C,D) (9,B),<br>
and the empty tile is at Row #1 (index starts from 0),<br>
so 14 + 1 = 15 is odd.<br>

You can see [here](https://www.cs.bham.ac.uk/~mdr/teaching/modules04/java2/TilesSolvability.html) to know why is that formula works.
Using:
------
If you don't know how to set. You can watch this [video](https://www.youtube.com/watch?v=axIgxBQVBg0) to set environment.
1. Run Visual Studio 2017 Community
2. Download [SFML 32-bit](https://www.sfml-dev.org/download.php) and [set](https://www.sfml-dev.org/tutorials/2.5/start-vc.php)
3. Create a folder under the project names **SFML** and copy folders into it.(bin, include, lib)
4. Bulid and run project
5. An error will appear. Copy dll files into **Debug** folder.(openal32.dll, sfml-audio-d-2.dll, sfml-graphics-d-2.dll, sfml-network-d-2.dll, sfml-system-d-2.dll, sfml-window-d-2.dll)
6. Rerun the project.

To be fix:
----------
&nbsp;&nbsp;-Can just show shortest path <= 26 steps limited by the program window size.<br>
&nbsp;&nbsp;&nbsp;If you want to see more than 26 steps, you can add "cout" into the *getPathString* function which in *A_star.cpp*. And then you can see all steps in CMD.
&nbsp;&nbsp;-Sometimes click "Show path" button will seems crash<br>
&nbsp;&nbsp;&nbsp;I don't know it is solve too complex puzzle takes very long time or just crash 
accidental. If it happens, just close the program and rerun.<br>

[Code reference](https://www.youtube.com/watch?v=NJZ2K6HPpl4)<br>
[Architecture reference](http://cjlin.nlplab.tw/AI1042_assignments.html)<br> Some examples and descriptions are just copy from here.<br>
[SFML](https://www.sfml-dev.org/)

-------

介紹：
----------
遊戲形式如下，可以滑動空格，你必須將其排序。<br>
| 2|24| 8| 5| 4|
|:--:|:--:|:--:|:--:|:--:|
|15|  |23|10| 9|
|20| 7|14|12| 3|
| 6|11|18|21|17|
|16| 1|22|13|19|
<br>
|&nbsp;| 1| 2| 3| 4|
|:--:|:--:|:--:|:--:|:--:|
| 5| 6| 7| 8| 9|
|10|11|12|13|14|
|15|16|17|18|19|
|20|21|22|23|24|
<br>
更多關於該遊戲的說明，可以參考[數字推盤遊戲（n-puzzle）](https://zh.wikipedia.org/wiki/%E6%95%B8%E5%AD%97%E6%8E%A8%E7%9B%A4%E9%81%8A%E6%88%B2)
程式執行結果如下圖。右邊顯示的路徑是利用[A* 演算法](https://zh.wikipedia.org/wiki/A*%E6%90%9C%E5%B0%8B%E6%BC%94%E7%AE%97%E6%B3%95)找出最短路徑，整個系統分成四個部分。
![GamePNG](https://i.imgur.com/lqrRdno.png)


<font size=4>**Part I: 判斷是否有解**</font>
這步不需要做，因為本程式**絕對**有解。該程式生成的隨機puzzle是由已排序好的puzzle亂數移動而成的。<br>

<font size=4>**Part II:  Manhattan distance**</font>
[Manhattan distance](https://zh.wikipedia.org/wiki/%E6%9B%BC%E5%93%88%E9%A0%93%E8%B7%9D%E9%9B%A2)
步驟:

1. 將題目視為 *n* × *n* 座標; 紀錄每個位置 (x<sub>i</sub>, y<sub>i</sub>)
2. 將排序好的狀態視為 *n* × *n* 紀錄每個位置 (a<sub>i</sub>, b<sub>i</sub>)
3. Manhattan distance 為 Σ<sub>i</sub> | x<sub>i</sub> - a<sub>i</sub> | + | y<sub>i</sub> - b<sub>i</sub> |

題目<br>
| 7| 2| 4|
|:--:|:--:|:--:|
| 5|  | 6|
| 8| 3| 1|
<br>
目標<br>
|&nbsp;| 1| 2|
|:--:|:--:|:--:|
| 3| 4| 5|
| 6| 7| 8|
<br>
|  數字|           目前位置|       目標位置|     Manhattan distance      |
|:----:|:---------------:|:------------:|:---------------------------:|
|     1|      (2,2)      |     (0,1)    |\|2-0\| + \|2-1\| = 2 + 1 = 3|
|     2|      (0,1)      |     (0,2)    |\|0-0\| + \|1-2\| = 0 + 1 = 1|
|     3|      (2,1)      |     (1,0)    |\|2-1\| + \|1-0\| = 1 + 1 = 2|
|     4|      (0,2)      |     (1,1)    |\|0-1\| + \|2-1\| = 1 + 1 = 2|
|     5|      (1,0)      |     (1,2)    |\|1-1\| + \|0-2\| = 0 + 2 = 2|
|     6|      (1,2)      |     (2,0)    |\|1-2\| + \|2-0\| = 1 + 2 = 3|
|     7|      (0,0)      |     (2,1)    |\|0-2\| + \|0-1\| = 2 + 1 = 3|
|     8|      (2,0)      |     (2,2)    |\|2-2\| + \|0-2\| = 0 + 2 = 2|
<br>
Manhattan distances和為: 18<br>

<font size=4>**Part III: Successor function**</font>
函數參數 = (stateRps, lastCostOfG, lastActionSequence)<br>
步驟:
1. 將題目視為 *n* × *n* 座標
2. 找出0的位置(x<sub>0</sub>, y<sub>0</sub>)
3. 如果0的四周(x<sub>0</sub>, y<sub>0</sub>-1), (x<sub>0</sub>, y<sub>0</sub>+1), (x<sub>0</sub>-1, y<sub>0</sub>), (x<sub>0</sub>+1, y<sub>0</sub>)有可合法移動的格子，將其交換

<font size=4>**Part IV: Priority queue**</font>
步驟:
1. 使用STL container的[priority_queue](http://www.cplusplus.com/reference/queue/priority_queue/)
2. 製作一個比較用的struct cmp給priority queue使用
3. 將Successor function得出的物件push進priority queue
4. Pop priority queue，會得到最小cost的行動
5. 再將剛剛pop出的物件放入Successor function，直到得出解

<font size=4>**補充**</font>
如果你想知道N-puzzle是否有解，先看看該puzzle的大小，*n* x *n*中的*n*為奇數還是偶數，其中
N = *n* x *n* - 1.<br>
如果*n*是奇數且反置(inversion)的數字為偶數，則有解
| 3| 1| 2|
|:--:|:--:|:--:|
| 4| 5| 7|
| 6| 8|  |
是無解的，因為該題目為 31245768 (去除 0) 有3對反置的數字: (1,3) (2,3) (6,7)<br><br>

如果*n*是偶數，且含有空格的那一列所在的列數 + 反置的數字和為偶數，則有解<br>
| 1| 2| 7| 4|
|:--:|:--:|:--:|:--:|
| 3|  | 6|10|
| 8| 5|13| 1|
| 9|12|14|15|
<br>
是無解的<br>
因為該題目為 127436A85DB9CEF (去除 0) 有14對反置的數字: (3,7) (4,7) (5,7) (6,7) (3,4) (5,6) (5,A) (8,A) (9,A) (5,8) (9,D) (B,D) (C,D) (9,B)<br>
且空格位於 Row #1 (由0開始算)<br>
所以 14 + 1 = 15 為奇數<br>

可以參考[這裡](https://www.cs.bham.ac.uk/~mdr/teaching/modules04/java2/TilesSolvability.html)來了解為何該公式是成立的

使用：
----------
如果你對設置有疑問，可以看這部[影片](https://www.youtube.com/watch?v=axIgxBQVBg0)教學
1. 開啟Visual Studio 2017 Community
2. 下載[SFML 32-bit](https://www.sfml-dev.org/download.php)並[設置環境](https://www.sfml-dev.org/tutorials/2.5/start-vc.php) 
3. 在專案底下開一個資料夾取名為SFML，並將下載的SFML裡面的三個資料夾(bin、include、lib)放進去
4. 建置並執行專案
5. 會出現一個錯誤。複製bin資料夾裡面的dll檔案(openal32.dll、sfml-audio-d-2.dll、sfml-graphics-d-2.dll、sfml-network-d-2.dll、sfml-system-d-2.dll、 sfml-window-d-2.dll)放進Debug資料夾內
6. 再次執行專案

待修正：
----------
&nbsp;&nbsp;-最短路徑最多只能顯示28步，因為程式視窗太小<br>
&nbsp;&nbsp;&nbsp;如果你想看更多步，可以在*A_star.cpp*裡面的*getPathString* function中增加"cout"，如此一來就可以在CMD視窗中看到所有步驟
&nbsp;&nbsp;-太複雜的puzzle會花非常長的時間來解
&nbsp;&nbsp;&nbsp;如果"Show path"執行太久都沒有得出解，請重啟程式
&nbsp;&nbsp;-有時點擊"Show path"按鈕程式好像會當機<br>
&nbsp;&nbsp;&nbsp;我不知道那是因為解一個太複雜的puzzle要花費非常多時間還是這只是偶發地發生。如果出現這種狀況，請重新執行程式<br>


[程式碼參考](https://www.youtube.com/watch?v=NJZ2K6HPpl4)<br>
[架構參考](http://cjlin.nlplab.tw/AI1042_assignments.html)<br> 有些範例與說明是直接從這裡複製<br>
[SFML](https://www.sfml-dev.org/)
