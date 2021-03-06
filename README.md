# 一步一步学编程

本教程的主要目的是引导大家通过合理的过程和步骤，一步一步掌握编程的理论与技巧，提高学习的效率和效果，并降低学习过程的痛苦指数。和其他传统的教程不同之处主要在于：1) 使用Git来记录学习过程的代码、心得：保存学习过程的进度，能够更好的师生互动; 2) 本教程只提供了学习大纲，需要找适合自己的教程，并自己设计学习进度和安排。**请有志于机器学习，计算机视觉的同学脚踏实地的把基础打扎实之后再开始相关专业知识的学习。**

注意：
* ***本教程主要是培养并锻炼算法思维，如果只是简单的抄别人的代码，毫无意义，所以大家宁愿慢一点也不要抄！！！***
* ***关于本教程的说明，请认真阅读三遍以上！***

![learn_programming](images/learn_programming.png)



## 一、为何学习编程？


编程，英语，数学是通往未来的三个主要钥匙。其中编程是让你实现梦想，英语是让你找到通往梦想的资料，数学是让你构建路径的模型和策略。上述三样能力都是需要长时间积累，很难在短时间突击提高，因此建议各位同学能够脚踏实地把基础打扎实，克服眼高手低的问题。由于研究生阶段学习时间比较短，需要同时学习大量的理论知识并完成大量的编程、实验，如果编程能力太弱，则导致研究过程处处受挫，从而丧失兴趣和目标。如果编程能力足够强大，则很多课题能够通过不断尝试、试错，找到解决问题的办法。总之编程能力的高低对研究生阶段的能力提升起到关键的作用，强烈建议各位同学切实重视编程功力的提升！


编程和很多其他的课程不一样，不是看看就能学会，需要不断的练习，不断的debug，不断的反思，不断的重构代码才能学好。其中各种语言是招式，相对好学；而算法、程序性思维是内功，并不容易提高。而内功的高低才正真决定了一个人编程能力的高低，希望大家能够通过坚持不懈的努力提高自己的功力。编程思维是一种综合的解决问题能力，由于计算机需要非常精确的指令才能正常工作，因此需要事前把每一个处理步骤的原理、实现都要搞得非常清楚，这样就锻炼了大家分析问题、设计流程、解决问题、总结反思等多方面的能力。



本教程提供了一个编程能力的综合学习引导，[预期需要达到的能力和技能](Target.md)主要包括：

* [C++语法、编程基础](1_c++)
    - **基本语法**：数据类型、循环、判断、选择、函数、指针、结构体和类
    - **输入与输出**：stdout打印输出，调试打印等
    - **文件读写**：文本文件，二进制存储
* [Git](6_tools/git), [Markdown](6_tools/markdown)
* [数据结构、算法](2_datastructure_algorithm)
    - 链表、二叉树、红黑树、图的遍历；
    - 查找，排序；
    - 动态规划、贪心算法
* [Linux](6_tools/linux)
    - 安装Linux
    - 常用命令
* IDE
    - 熟悉自己所用的IDE （建议[QtCreator](https://blog.csdn.net/sinat_27554409/article/details/78171499)）
* [Debug能力](6_tools/debug)
    - 学会debug
    - 单元测试
* 第三方库
    - Qt，OpenGL
    - Eigen3
    - OpenCV
* [综合练习，小项目（小游戏，模拟仿真程序）](4_projects)
* 高级技巧（[CMake](6_tools/cmake)，[库编写](5_advanced/3_Library)）
    - 使用Makefile或者CMake编写项目编译脚本等
    - 如何把常用的程序组织成库（静态库，动态库）
* [代码规范](5_advanced/programming_standard)
* [设计模式](5_advanced/4_DesignPattern_UML)
* 编程思维，分析问题、分解问题、解决问题能力

通过这个综合练习，为后续研究生阶段研究项目的编程打下坚实的基础，缩短研究过程试错周期，从而让研究生阶段能够学到更多知识、取得更大的成绩，希望大家能够认真对待！



## 二、如何学习？

大部分的计算机视觉、机器学习算法的底层代码通过C++来实现，另外经典的算法教程通过C/C++来讲授，因此需要把C++学好。但是C++非常博大精深，很难一上来就全部学会，因此需要采用**循环迭代**的学习方法，即通过多次from the shallower to the deeper的学习过程实现高效率的学习。比较高级、复杂的语言特性不用一上来就去学，可以等基本语法、常用数据结构学的比较扎实之后再着手高级的语法、技巧等。或者等基本语法、用法学完之后，在做练习题目的时候琢磨高级语法特性、技巧，体会为什么要设计这些高级用法，这样的学习有的放矢，效率更高。

主要的学习阶段和步骤分为如下的5个阶段，可以同时进行两个或以上的内容学习和练习，从而提高整体的学习效率。

### 2.1 [Stage 1: C++基础](1_c++/README.md) 

**需要在2周-3周完成：**

- 找一本C++的书 （教材就可以，或者如下的资料），将其中的基本内容快速过一遍（大约4-8天）
- 在C++基本用法的同时开始编程练习，例如书每一部分的练习题，或者参考[《编程练习题》](1_c++/CodePractice.md)
- 将其中的练习题做一遍（大约2周，给自己限定一个时间，必须快速完成）
- 在学习过程考虑，如何更有效的编程，如何提高debug能力
- 资料（可以使用在线的教程，或者自己找比较合适的）：
    - [《C++ 教程》](http://www.runoob.com/cplusplus/cpp-tutorial.html) ，通过这个教程快速学会C++的语法等。
    - 如果对自己有更高的要求，可以学习《[C++ Primer》](https://www.zhihu.com/question/32087709)。不过最好还是用上面普通的教程先把基础知识学好之后，把Stage4的小项目做完之后，再学习C++ Primer更有效率。

### 2.2 [Stage 2: 算法](2_datastructure_algorithm/README.md)

**需要在3周-6周完成：**

- 推荐下面的[《数据结构与算法入门》](https://www.dotcpp.com/course/ds/)，先把各种数据结构和基本的几种算法思维学会。如果对自己有更高的要求，可以学习《算法导论》
- 根据自己的基础，把重要的内容学一下，并尝试将算法练习题自己实现一下 （大约3-6周）
- 实现过程需要思考，算法的本质是什么，如何将算法转化成循环、判断
- 如何实现算法，如何测试代码，如何构建测试数据
- 可以参考一些教程，加快学习速度，例如：
    - [《数据结构与算法入门》](https://www.dotcpp.com/course/ds/)，学习基础的数据结构和算法知识，能够编写简单的算法题目。
    - [麻省理工学院公开课：算法导论](http://open.163.com/special/opencourse/algorithms.html) ， [你是如何坚持读完《算法导论》这本书的？](https://www.zhihu.com/question/27744730)，如果对自己要求更高，可以通过学习算法导论掌握更深的算法分析能力。

### 2.3 [Stage 3: 在线编程练习](3_code_practice/README.md) 

**需要在3周-6周完成：**

- 在基础知识学习到一定程度之后，需要找一些算法练习题目来继续提高自己的能力
- 如果自己想不到很好的练习题目，可以通过做 [《leetcode在线网站》](https://leetcode-cn.com/) 的练习题，来练习
- 需要完成50-200道题目的练习，各种类型的题目都需要做一些
- 可以根据自己的能力，选择如下的练习来完成
    - [初级算法 - 帮助入门](https://leetcode-cn.com/explore/interview/card/top-interview-questions-easy/)
    - [中级算法 - 巩固训练](https://leetcode-cn.com/explore/interview/card/top-interview-questions-medium/)
    - [高级算法 - 提升进阶](https://leetcode-cn.com/explore/interview/card/top-interview-questions-hard/)

### 2.4 [Stage 4: 综合编程练习项目](4_projects/README.md) 

**需要在2周-4周完成：**

- 可以思考一下，如何将所学的编程知识去解决一些实际问题
- 通过这个综合练习，运用所学的知识解决一个或者多个实际问题，从而锻炼系统性解决问题的能力，并提高思维水平
- 如果自己想不到太好的例子，可以参考所列的：[《综合练习例子程序》](4_projects/README.md)

### 2.5 [Stage 5: 高级技巧](5_advanced/README.md) 

**需要在2周-4周完成：**

- 如何把自己代码写的更规范：命名、格式、函数、类等。
    - 参考[《编码规范》](5_advanced/programming_standard)，将自己写过的代码按照规范进行格式、写法的调整
- 琢磨如何将前面所写的代码进行重构，如何提高代码的复用能力
    - 思考程序哪里写的不好，不容易理解，如何才能更好理解
    - 程序是否结构不清晰，如何分割成更好的函数、类
    - 思考那些函数、类是可以复用的，可以写成头文件
- 如何利用[CMake](6_tools/cmake)，[PICMake](6_tools/cmake/PICMake.md)将所有的代码组织起来，一次将自己编写的代码自动编译出来
    - 将自己C++（[Stage1](1_c++)），数据结构([Stage2](2_datastructure_algorithm))，综合练习项目（[Stage4](4_projects/README.md)）的程序用CMake组织起来
- 研究、学习如何将常用的函数、类组织到一个代码库，后续直接使用
    - 分析哪些函数、类可以复用，将可以复用的写成库
- 如何让代码更清晰易懂，在什么地方用什么[设计模式](5_advanced/4_DesignPattern_UML)？
	- 分析程序常用几种写法、模式，学习[设计模式](5_advanced/4_DesignPattern_UML)
	- 按照[设计模式](5_advanced/4_DesignPattern_UML)的方法，将自己的程序优化一下
- 掌握[多种编程工具](6_tools)的用法
- 在用的过程多琢磨技巧，并不断总结

### 2.6 [Stage 6: 高级项目](6_adv_projects) 

**需要在2周-4周完成，为更好的提高自己的能力建议完成：**

- 在学习基本工具的基础上，通过完成一个更复杂一点的项目，将编程语言、数据结构、工具、Debug、设计模式等多种技能进行综合练习，巩固所学的知识和技能。

### 2.7 [Stage 7: 高级C++](7_adv_c++) 

**需要在2周-4周完成，为更好的提高自己的能力建议完成：**

- 主要学习C++ 11， C++14， C++20等最新功能、函数。
- 目前主流的高端项目使用了大量的高级C++技巧，因此为了能编写复杂软件系统，建议好好学习一下高级C++

### 2.8 恭喜通关！

如果你能坚持到这个阶段，说明你编程功力很强了！可以自由遨游于机器的世界，充分发挥你的能力去创造奇迹！



## 三、如何提交作业，如何使用Git，Markdown

***请认真阅读具体要求和操作步骤，如果有不清楚的地方请及时咨询。***


### 3.1 具体要求：

1. 根据自己的学习过程，将所编写的程序保存到对应的目录里，分门别类存放程序、文档（养成条理的习惯）
2. 学习使用[《Git》](6_tools/git/README.md)，将代码、报告提交到[Gitee](https://gitee.com)
3. 可以参考[《报告例子》](report/20200511_report_demo.md)来写每周的报告。其中关于[Markdown](6_tools/markdown/README.md)的用法可以通过学习资料进行学习


### 3.2 具体操作步骤：

* [大家fork这个项目到自己的项目](6_tools/git/HowToForkClone.md)
* [然后git clone自己的项目到本地机器](6_tools/git/HowToForkClone.md)
* 在各目录里写入各自的代码、报告等
* 提交代码到本地仓库
```
git add -A
git commit -m "Change log"
```
* 通过`git push origin master`上传作业到自己的项目里。

每次完成一个作业就提交代码一次，或者每天完成之后提交一次代码。




其他说明：

* 关于Git和Gitee的操作可以深入学习[《Git教程》](6_tools/git/README.md)。

* 可以参考[《Gitee增加用户》](6_tools/git/gitee_addmember.md)来增加用户，**将邀请链接地址发送给`bushuhui@nwpu.edu.cn`** （重要步骤，请不要忘记遗漏！），从而加提高协同便捷性。大家提交作业后，我会在大家的项目里写入批注、建议等等，从而构建良好的反馈机制，能够更有效的取得学习效果。

* 可以安装Git客户端软件[GitKraken](https://www.gitkraken.com)，能够方便查看每次的提交都有那些更改，或者查看有那些批注、建议等。

* 如果无法提交代码到服务器，可以尝试将服务器最新的代码更新到本地，执行操作: `git pull origin master`。合并完成之后再执行代码提交`git push origin master`

* 关于Markdown，可以参考[《Markdown教程》](6_tools/markdown)，可以安装[Typora软件](https://typora.io)来编写Markdown，这个软件最大的特点是能够及时看到最终的效果。



## 四、学习的建议

本学习材料主要针对有意提高自我编程能力的学生，通过本学习材料能够学习得到研究生阶段所需要的编程基础知识、技能。**通过系统化的练习能够将所学的知识串联起来，从而提高学习的效率和效果**。由于人工智能技术飞速的发展，所以想要在研究生阶段取得更好的成绩需要非常强的自学能力，在学习本系列教程的过程中，**需要自己不断的反思，如何才能更有效的学习？怎么才能抓住所学科目的重点？如果遇到不会的问题，如何去找资料？什么样的问题去问？什么样的问题要自己去找答案？**

**本教程和习题和传统的课程很大的不同点在于：必须通过自己的编程、实践，唯有自己亲自练习才能真正学到各个科目的精髓，才能切实地提升自己的能力，从而摆脱眼高手低的问题。另外本教程给出的参考资料并不是很完善，需要自己去找适合自己的学习材料，这是为了锻炼自己找资料的能力。**

1. **每次完成一个编程题目就提交一次代码，或者每天完成学习、练习之后就提交一次代码。**

2. 要有良好的心态，这是为自己学习，不是应付一件差事。未来的世界是机器的世界，如果不会写程序将寸步难行。学习写程序和成为码农没有必然的联系，而是扩展自己认知范围的一种重要方向，因为程序性思维是一类非常重要的思维技能。编程作为机器时代的必备技能，如果不会编程将会是未来的“文盲”，所以需要从认识上尽可能降低排斥心理。**在一个小学生都在学习编程的时代，作为一个20多岁精力最为旺盛的研究生如果不会写程序，如何面对这个时代？**

3. 编程、算法和很多其他课程不一样，不是花几天突击一下就能提高的；而是需要坚持一段时间持续不断的锻炼、思考，突然一天才发现自己能力提升了。因此建议大家根据自己其他课程、时间等，合理安排学习编程的时间，坚持每周都做一些题目，每周至少抽出半天来练习编程和算法。

4. **不能直接抄已有的程序，或者抄别人的程序**，如果自己不会要自己去想，去找解决方法，或者去问。如果直接抄别人的代码，这样的练习一点意义都没有。在这个阶段大家静下心提高编程思维能力，为后续的研究打好基础，否则后续的研究过程不仅做不了深入的研究，而且做东西会比较慢。**如果感觉太难，可以做的慢一些，但是坚持自己思考、自己编写代码**。**这个练习重要的是通过自己思考、尝试，从而构建自己的思维系统，只有通过练习才能锻炼并提高自己的真正的能力**。

5. **请先遍历一遍这个文件夹和所有的子文件夹，了解有什么内容，资料**。各个目录里有很多说明文档，如果不会先找找有没有文档，如果找不到合适的文档就去网上找找。通过这个过程锻炼自己搜索文献、资料的能力。

6. 不要想一次就把编程、算法学精通！由于存在大量的概念、复杂思维、大量的技巧等，比较短的时间大部分人的大脑是无法接收并理解如此多的东西，因此使用iterative学习方法比较有效率。先把简单的C++/数据结构的书、教程学完一遍，然后开始练程序，等练完之后再进入更深一层的理论学习，例如《C++ Primer》或者《算法导论》等书。编程和其他课程有非常大的不同，需要自己在编程过程体会每个知识点的具体含义，只有在实际编程过程才会学到很多书上没有的技巧、解决问题的思路等等。一句话就是：不要怕，马上开始真实的练习！

7. 做习题的过程不要着急，如果感觉难，无从下手，可以在自己之前的代码基础上修改，逐步实现需要的功能；或者想办法简化任务，等简单的完成之后在增加细节，直到原始问题被解决。**只有自己写才最锻炼，看上去慢，实际上是最快，最有效的学习方式，这样才能更深刻的理解算法的思维**。要把算法思维搞懂，只要能搞懂，后面的内容学起来就很快。其实算法思维没有几类，前面的真正掌握了，后面的学起来很快的。

8. 在学习、编写练习题目的时候，有太多概念、操作过程复杂，脑子比较混乱，如果这样不要着急！慢慢来！**本教程主要目的，就是要你脑子糊涂，然后通过自己的思维把各种关系、流程理顺，从而学会如何思考解决复杂问题。本学习的主要目的是要强化这个由混乱到清晰的过程，而不是最终的代码，这就是内功心法**。编程语言等招式通过记忆就可以学会，而最重要的思维、内功别人没有办法教，只有自己悟出来的才算是真正掌握。

9. 这些课题最好使用[《Linux》](6_tools/linux)以及Linux下的开发工具来做。逼迫自己使用[《Linux》](6_tools/linux)，只有多练、多用才能快速进步。如果实在太难，先在虚拟机里装一个Linux（例如Ubuntu，或者LinuxMint等），先熟悉一下。但是最终需要学会使用Linux。

10. **制定计划，严格按照自己设定的时间节点来完成。如果有拖延症，努力克服自己的拖延症**。

11. 写程序要细心，一个很小的错误导致程序不能正确运行。通过不断的debug提高自己排错的能力。

12. 学习过程要多思考，思考什么是程序？程序为什么这样写？有没有更好的方法来解决问题？怎么才能优化地更好，让程序执行的更快？怎么才能把函数、功能封装起来。总之要多想。

13. 不仅要将程序写出来，还要把写程序过程中遇到的问题，如何解决的都写到报告里。报告要包括：程序目的，算法，难点问题，结果，思考等。

14. 如果学习基本语法、写基本的C++程序疲惫了，可以尝试做一下[《第四阶段的小项目》](4_projects)或者[《第三阶段的算法练习题》](3_code_practice)换换脑子。通过做小项目或算法练习题，发现自己的短板，从而有针对性的学习。

15. 这个练习的最主要的目的是通过[《Stage4的综合练习》](4_projects)来牵引学习C++，数据结构、算法等。通过这个学习过程让自己学会一种思维，如果遇到解决不了的问题，如何去找到解决这个大、难问题的子问题，并通过什么途径一个一个去解决，从而最终把大的难题解决。

16. 要相信奇迹会发生，自己只要能坚持把Stage4做完，能力就会有比较大的提升。根据以往的经验，这个练习题做完的同学，解决问题、编程思维等能力都有很大的提升，所以需要让自己坚信，内功真的需要一层一层修炼。

17. 完成编程练习，[《Stage4的综合练习》](4_projects)等，往往编写的程序比较混乱、代码不清晰、复用能力比较弱。需要通过多次的[《代码重构》](5_advanced/README.md)来提高自己的综合编程能力，在多次的代码重构过程中，提升自己的逻辑思维能力、工具和技巧等方面的能力。




## 五、相关学习资料参考

在上述内容学习完成之后，可以进行机器学习、计算机视觉方面的学习与研究，具体的资料可以参考：
1. 飞行器智能感知与控制实验室 - 培训教程与作业
    - [《飞行器智能感知与控制实验室-暑期培训教程》](https://gitee.com/pi-lab/SummerCamp)
    - [《飞行器智能感知与控制实验室-暑期培训作业》](https://gitee.com/pi-lab/SummerCampHomework)
2. 机器学习教程与作业
    - [《机器学习教程》](https://gitee.com/pi-lab/machinelearning_notebook)
    - [《机器学习课程作业》](https://gitee.com/pi-lab/machinelearning_homework)
3. [《一步一步学SLAM》](https://gitee.com/pi-lab/learn_slam)
4. [《一步一步学ROS》](https://gitee.com/pi-lab/learn_ros)
5. [飞行器智能感知与控制实验室-研究课题](https://gitee.com/pi-lab/pilab_research_fields)
6. [编程代码参考、技巧集合](https://gitee.com/pi-lab/code_cook)
    - 可以在这个代码、技巧集合中找到某项功能的示例，从而加快自己代码的编写



### 5.1 工具的使用教程等

* [Code Cook - 编程参考代码，技巧集合](https://gitee.com/pi-lab/code_cook)
* [Linux](6_tools/linux/README.md)
* [Markdown](6_tools/markdown/README.md)
* [Git](6_tools/git/README.md)
* [CMake](6_tools/cmake/README.md)



### 5.2 参考资料：

* [C++的算法、程序大全](https://github.com/TheAlgorithms/C-Plus-Plus)
