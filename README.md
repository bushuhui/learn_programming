本教程的主要目的是帮助大家能够快速掌握编程，和其他的传统的教程不同之处主要在于：1) 使用Git来记录学习过程：保存学习过程的进度，能够更好的互动; 2) 本教程只提供了学习的大纲，需要自己找适合自己的教程，并自己设计学习进度和安排。请有志于机器学习，计算机视觉的同学脚踏实地的把基础打扎实之后再开始相关专业知识的学习。

***本教程主要是培养并锻炼算法思维，如果只是简单的抄别人的代码，毫无意义，所以大家宁愿慢一点也不要抄！！！***

***关于本教程的说明，请认真阅读三遍以上！***



## 一、为何学习编程？


编程，英语，数学是通往未来的三个主要钥匙。其中编程是让你实现梦想，英语是让你找到通往梦想的资料，数学是让你构建路径的模型和策略。因此建议各位同学能够脚踏实地把基础打扎实，克服眼高手低的问题。


编程和很多其他的课程不一样，不是看看就能学会，需要不断的练习，不断的debug，不断的反思，不断的重构代码才能学好。其中各种语言是招式，相对好学；而算法、程序性思维是内功，并不容易提高。而内功的高低才正真决定了一个人编程能力的高低，希望大家能够通过坚持不懈的努力提高自己的功力。



## 二、如何学习？

因为主要的计算机视觉、机器学习算法的底层通过C++来实现，因此需要把C++学好。但是C++比较博大精深，很难一上来就全部学会，因此需要采用逐步学习的方法。比较高级、复杂的语言特性不用一上来就去学，可以等基本语法、常用数据结构学的比较扎实之后再着手高级的语法、技巧等。

主要的学习阶段和步骤分为如下的5个阶段，可以同时进行两个或以上的内容同时学习和练习，从而提高整体的学习效率。


[Stage 1: C++基础](1_c++/README.md)
- 找一本C++的书 （教材就可以，或者如下的资料），将其中的基本内容快速过一遍
- 将其中的练习题做一遍（大约2周，给自己限定一个时间，必须快速完成）
- 在学习过程考虑，如何更有效的编程，如何提高debug能力
- 资料（可以使用在线的教程，或者自己找比较合适的）：
    - [C++ 教程](http://www.runoob.com/cplusplus/cpp-tutorial.html) ，通过这个教程快速学会C++的语法等。
    - 如果对自己有更高的要求，可以学习[C++ Primer](https://www.zhihu.com/question/32087709)。不过最好还是用上面普通的教程先把基础知识学好之后，再学习C++ Primer更有效率。


[Stage 2: 算法](2_datastructure_algorithm/README.md)
- 推荐下面的《数据结构与算法入门》，先把各种数据结构和基本的几种算法思维学会。如果对自己有更高的要求，可以学习《算法导论》
- 根据自己的基础，把重要的内容学一下，并尝试将算法练习题自己实现一下 （大约4-8周）
- 实现过程需要思考，算法的本质是什么，如何将算法转化成循环、判断
- 如何实现算法，如何测试代码，如何构建输入数据
- 可以参考一些教程，加快学习速度，例如：
    - [数据结构与算法入门](https://www.dotcpp.com/course/ds/)，学习基础的数据结构和算法知识，能够编写简单的算法题目。
    - [麻省理工学院公开课：算法导论](http://open.163.com/special/opencourse/algorithms.html) [你是如何坚持读完《算法导论》这本书的？](https://www.zhihu.com/question/27744730)，如果对自己要求更高，可以通过学习算法导论掌握更深的算法分析能力。


[Stage 3: 在线编程练习](3_code_practice/README.md)
- 在基础知识学习到一定程度之后，需要找一些算法练习题目来继续提高自己的能力
- 如果自己想不到很好的练习题目，可以通过做[leetcode](https://leetcode-cn.com/)等在线网站的练习题，来练习
- 需要完成20-50道题目的练习，各种类型的题目都需要做一些
- 可以根据自己的能力，选择如下的练习来完成
    - [初级算法 - 帮助入门](https://leetcode-cn.com/explore/interview/card/top-interview-questions-easy/)
    - [中级算法 - 巩固训练](https://leetcode-cn.com/explore/interview/card/top-interview-questions-medium/)
    - [高级算法 - 提升进阶](https://leetcode-cn.com/explore/interview/card/top-interview-questions-hard/)


[Stage 4: 综合性质的编程练习项目](4_projects/README.md)
- 可以思考一下，如何将所学的编程知识去解决一些实际的问题
- 通过这个综合练习，运用所学的知识解决一个或者多个实际的问题，并锻炼系统性的解决问题思路
- 如果自己想不到太好的例子，可以参考给出的几个[例子程序](4_projects/README.md)
    - 例1：如何自己编写一个自动下五子棋的程序，思考编写这样的程序需要什么样的技术，需要什么算法，如何保存棋盘的状态，如何有效判断在何位置下子最好等等
    - 例2：如何自己编写一个数独的自动求解、推理程序，类似的思考如何才能自己实现这样的程序
    - 更多的例子和说明可以参考[例子程序](4_projects/README.md)


[Stage 5: 高级技巧](5_advanced/README.md)
- 琢磨如何将前面所写的代码进行重构，如何提高代码的复用能力
- 如何利用CMake，PICMake将所有的代码组织起来，一次将自己编写的代码都编译出来
- 研究、学习如何将常用的函数、类组织到一个代码库，后续直接使用



### 重点掌握下列知识点和技能：

* **基本语法**：数据类型、循环、判断、选择、函数、指针、结构体和类
* **输入与输出**：stdout打印输出，调试打印等
* **文件读写**：文本文件，二进制存储
* **数据结构与算法**：链表、二叉树、红黑树、图的遍历；查找，排序；动态规划、贪心算法
* **如何使用编程工具**：熟悉自己所用的IDE，如何debug；尝试学习Linux，并尝试使用Makefile或者CMake编写项目编译脚本等




## 三、如何提交作业，如何使用git，markdown

***请认真阅读具体要求和操作步骤，如果有不清楚的地方请及时咨询。***


### 3.1 具体要求：

1. 根据自己的学习过程，将所编写的程序保存到对应的目录里，分门别类存放程序（养成条理的习惯）
2. 学习使用[git](6_tools/git)，将代码、报告提交到[gitee](https://gitee.com)
3. 可以参考[报告例子](report/20190304_report_demo.md)来写每周的报告。其中关于[Markdown](6_tools/markdown)的用法可以通过学习资料进行学习


### 3.2 具体的操作步骤：

* 大家fork这个项目到自己的项目
* 然后git clone自己的项目到本地机器
* 在各目录里写入各自的代码、报告等
* 通过`git push origin master`上传作业到自己的项目里。每次完成一个作业就提交代码一次，或者每天完成之后提交一次代码。
* 由于本作业会更新因此需要更新到最新的版本，可以如下操作
```
git remote add upstream git@gitee.com:pi-lab/learn_programming.git
git pull upstream master
```

关于Git和Gitee的操作可以深入学习[git教程](6_tools/git/README.md)。可以参考[Gitee增加用户](6_tools/git/gitee_addmember.md)来增加用户，将邀请链接地址发送给`bushuhui@nwpu.edu.cn`，从而加快协同便捷性。大家提交作业后，我会在大家的项目里写入批注、建议等等，从而构建良好的反馈机制，能够更有效的取得学习效果。

可以安装git客户端软件[GitKraken](https://www.gitkraken.com)，能够方便查看每次的提交都有那些更改，或者查看有那些批注、建议等。

如果无法提交代码到服务器，可以尝试将服务器最新的代码更新到本地，执行操作: `git pull origin master`。合并完成之后再执行代码提交`git push origin master`



## 四、学习的建议

本学习材料主要针对有意提高自我编程能力的学生，通过本学习材料能够学习得到后续研究生阶段所需要的基础知识、技能。通过系统化的练习能够将所学的知识串联起来，从而提高学习的效率和效果。由于人工智能技术飞速的发展，所以想要在研究生阶段取得更好的成绩需要非常强的自学能力，在学习本系列教程的过程中，需要自己不断的反思，如何才能更有效的学习？怎么才能抓住所学科目的重点？如果遇到不会的问题，如何去找资料？什么样的问题去问？什么样的问题要自己去找答案？

**本教程和习题和传统的课程很大的不同点在于：必须通过自己的编程、实践，唯有自己亲自练习才能真正学到各个科目的精髓，才能切实地提升自己的能力，从而摆脱眼高手低的问题。另外本教程给出的参考资料并不是很完善，需要自己去找适合自己的学习材料，这是为了锻炼自己找资料的能力。**

0. **每次完成一个编程题目就提交一次代码，或者每天完成学习、练习之后就提交一次代码。**
1. **不能直接抄已有的程序，或者抄别人的程序**，如果自己不会要自己去想，去找解决方法，或者去问。如果直接抄别人的代码，这样的练习一点意义都没有。在这个阶段大家静下心提高编程思维能力，为后续的研究打好基础，否则后续的研究过程不仅做不了深入的研究，而且做东西会比较慢。如果感觉太难，可以做的慢一些，但是坚持自己思考、自己编写代码。这个练习重要的是通过自己思考、尝试，从而构建自己的思维系统，只有通过练习才能锻炼并提高自己的真正的能力。
2. **请先遍历一遍这个文件夹和所有的子文件夹，了解有什么内容，资料**。各个目录里有很多说明文档，如果不会先找找有没有文档，如果找不到合适的文档就去网上找找。通过这个过程锻炼自己搜索文献、资料的能力。
3. 要有良好的心态，这是为自己学习，不是应付一件差事。未来的世界是机器的世界，如果不会写程序将寸步难行。
4. 做习题的过程不要着急，如果感觉难，无从下手，可以在自己之前的代码基础上修改，逐步实现需要的功能；或者想办法简化任务，等简单的完成之后在增加细节，直到原始问题被解决。**只有自己写才最锻炼，看上去慢，实际上是最快，最有效的学习方式，这样才能更深刻的理解算法的思维**。要把算法思维搞懂，只要能搞懂，后面的内容学起来就很快。其实算法思维没有几类，前面的真正掌握了，后面的学起来很快的。
5. 在学习、编写练习题目的时候，有太多概念、操作过程复杂，脑子比较混乱，如果这样不要着急！慢慢来！。本教程的主要目的，就是要你脑子糊涂，然后通过自己的思维把各种关系、流程理顺，从而学会如何思考解决复杂问题。本学习的主要目的是要强化这个由混乱到清晰的过程，而不是最终的代码，这就是内功心法。编程语言等招式通过记忆就可以学会，而最重要的思维、内功别人没有办法教，只有自己悟出来的才算是真正掌握。
6. 这些课题最好使用Linux以及Linux下的开发工具来做。逼迫自己使用Linux，只有多练、多用才能快速进步。如果实在太难，先在虚拟机里装一个Linux（例如Ubuntu，或者LinuxMint等），先熟悉一下。但是最终需要学会使用Linux。
7. 制定计划，严格按照自己设定的时间节点来完成。如果有拖延症，努力克服自己的拖延症。
8. 写程序要细心，一个很小的错误导致程序不能正确运行。通过不断的debug提高自己排错的能力。
9. 学习过程要多思考，思考什么是程序？程序为什么这样写？有没有更好的方法来解决问题？怎么才能优化地更好，让程序执行的更快？怎么才能把函数、功能封装起来。总之要多想。
10. 不仅要将程序写出来，还要把写程序过程中遇到的问题，如何解决的都写到报告里。报告要包括：程序目的，算法，难点问题，结果，思考等。


## 五、相关学习资料参考

在上述内容学习完成之后，可以进行计算视觉、机器学习方面知识的学习，具体的资料可以参考：
1. 智能系统实验室-培训教程与作业
    - [智能系统实验室-新人暑期培训教程](https://gitee.com/pi-lab/SummerCamp)
    - [智能系统实验室-新人暑期培训作业](https://gitee.com/pi-lab/SummerCampHomework)
2. 机器学习教程与作业
    - [机器学习教程](https://gitee.com/pi-lab/machinelearning_notebook)
    - [机器学习课程作业](https://gitee.com/pi-lab/machinelearning_homework)
3. [智能系统实验室研究课题](https://gitee.com/pi-lab/pilab_research_fields)
4. [编程代码参考、技巧集合](https://gitee.com/pi-lab/code_cook)
    - 可以在这个代码、技巧集合中找到某项功能的示例，从而加快自己代码的编写


工具的使用教程等
* [Code Cook - 编程参考代码，技巧集合](https://gitee.com/pi-lab/code_cook)
* [Linux](6_tools/linux)
* [Markdown](6_tools/markdown)
* [Git](6_tools/git)
* [CMake](6_tools/cmake)

