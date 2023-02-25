# 基于SVar的模块化编程





## 问题

* SVar定义的接口函数，是否支持STL等类型，例如 `vector<double>` 等。可以的，通过`Svar.castAs<vector<UserData>>()`