# Back trace & Dump



## [breakpad](https://chromium.googlesource.com/breakpad/breakpad)

* [使用 Google Breakpad 来助力解决程序崩溃](https://cloud.tencent.com/developer/article/2194607)

Google Breakpad 是 Google 开发的一个跨平台的崩溃采集库。利用这个库可以在 Windows, Mac, Linux, iOS 和 Android 平台上对程序的崩溃进行捕获，并生成 dump 文件供后期分析。也是目前最成熟运用最广的开源库，并且这个库现在依然在更新和维护。

它主要包括三个部分：
* dumpSyms 负责读取用户开发应用中的debug信息，并生成特定的符号文件。
* client 在崩溃系统中负责抓取当前线程和当前载入的库生成 minidump 文件。
* processor 通过 minidump_stackwalk 读取 minidump 文件 找到合适的符号文件产生一个可读的 c/c++ 调用栈。