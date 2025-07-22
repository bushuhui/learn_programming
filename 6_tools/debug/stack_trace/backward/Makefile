CXX = g++
CXXFLAGS = -g -rdynamic -fPIC -std=c++11
LDFLAGS = -lbfd -lunwind -ldl

# 目标文件
TARGETS = stack_trace_test libcrash.so
CRASH_LIB_SRC = crash_lib.cpp
MAIN_SRC = test_dl_crash.cpp backward.cpp

.PHONY: all clean install-deps check-deps

all: check-deps $(TARGETS)

# 检查依赖库是否安装
check-deps:
	@echo "检查依赖库..."
	@pkg-config --exists libunwind || (echo "错误: libunwind 未安装. 请运行: sudo apt install libunwind-dev" && exit 1)
	@ldconfig -p | grep libbfd > /dev/null || (echo "错误: libbfd 未安装. 请运行: sudo apt install binutils-dev" && exit 1)
	@echo "依赖库检查通过!"

# 安装依赖库
install-deps:
	@echo "安装依赖库..."
	sudo apt update
	sudo apt install -y libunwind-dev binutils-dev

# 构建动态库
libcrash.so: $(CRASH_LIB_SRC) crash_lib.h
	$(CXX) $(CXXFLAGS) -shared -o $@ $(CRASH_LIB_SRC)
	@echo "动态库 libcrash.so 构建完成"

# 构建主程序
stack_trace_test: $(MAIN_SRC) backward.hpp libcrash.so
	$(CXX) $(CXXFLAGS) -DBACKWARD_HAS_BFD=1 -DBACKWARD_HAS_LIBUNWIND=1 -o $@ $(MAIN_SRC) $(LDFLAGS)
	@echo "主程序 stack_trace_test 构建完成"

# 运行测试
run: all
	@echo "运行堆栈回溯测试..."
	./stack_trace_test

# 清理
clean:
	rm -f $(TARGETS)
	@echo "清理完成"

# 显示帮助
help:
	@echo "可用目标:"
	@echo "  all          - 构建所有目标"
	@echo "  check-deps   - 检查依赖库"
	@echo "  install-deps - 安装依赖库"
	@echo "  run          - 构建并运行测试"
	@echo "  clean        - 清理构建文件"
	@echo "  help         - 显示此帮助信息"