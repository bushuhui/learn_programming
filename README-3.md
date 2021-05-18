
## 三、如何提交作业，如何使用Git，Markdown

***请认真阅读具体要求和操作步骤，如果有不清楚的地方请及时咨询。***


### 3.1 具体要求：

1. 根据自己的学习过程，将所编写的程序保存到对应的目录里，分门别类存放程序、文档（养成条理的习惯）
2. 学习使用[《Git》](6_tools/git)，将代码、报告提交到[Gitee](https://gitee.com)
3. 可以参考[《报告例子》](report/20200511_report_demo.md)来写每周的报告。其中关于[Markdown](6_tools/markdown)的用法可以通过学习资料进行学习


### 3.2 具体操作步骤：

* [大家fork这个项目到自己的项目](6_tools/git/HowToForkClone.md)
* [然后git clone自己的项目到本地机器](6_tools/git/HowToForkClone.md)
* 在各目录里写入各自的代码、报告等
* 通过`git push origin master`上传作业到自己的项目里。每次完成一个作业就提交代码一次，或者每天完成之后提交一次代码。
* 由于本作业会更新因此需要更新到最新的版本，可以如下操作
```
git remote add upstream git@gitee.com:pi-lab/learn_programming.git
git pull upstream master
```



其他说明：

* 关于Git和Gitee的操作可以深入学习[《Git教程》](6_tools/git/README.md)。

* 可以参考[《Gitee增加用户》](6_tools/git/gitee_addmember.md)来增加用户，**将邀请链接地址发送给`bushuhui@nwpu.edu.cn`** （重要步骤，请不要忘记遗漏），从而加提高协同便捷性。大家提交作业后，我会在大家的项目里写入批注、建议等等，从而构建良好的反馈机制，能够更有效的取得学习效果。

* 可以安装Git客户端软件[GitKraken](https://www.gitkraken.com)，能够方便查看每次的提交都有那些更改，或者查看有那些批注、建议等。

* 如果无法提交代码到服务器，可以尝试将服务器最新的代码更新到本地，执行操作: `git pull origin master`。合并完成之后再执行代码提交`git push origin master`

* 关于Markdown，可以参考[《Markdown教程》](6_tools/markdown)，可以安装[Typora软件](https://typora.io)来编写Markdown，这个软件最大的特点是能够及时看到最终的效果。



