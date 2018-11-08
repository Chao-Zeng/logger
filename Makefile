#author ����
#ͨ��Makefile�ļ�

#makeĿ��
.PHONY: all clean

#����release�汾�򿪴�ע��,Ĭ�Ϲرձ���debug�汾
#COMPILE = release
ifeq ($(COMPILE), release)
	RELEASE=1
endif

#���붯̬��򿪴�ע��,Ĭ�ϱ����ִ�г���
COMPILE_SHARED_LIB = 1

#Դ�ļ�Ŀ¼
DIR_SRCS = ./logger

#���ɵĿ�ִ�г���Ŀ¼
DIR_EXES = ./app

#��ִ�г�����
EXE = exe

#���ɵĶ�̬��Ŀ¼
DIR_LIBS = ./lib

#��̬������
ifndef RELEASE
	SHARED_LIB_NAME = liblog-1.0.0.so
else
	SHARED_LIB_NAME = liblog-1.0.0.so
endif

#����Ŀ��
ifdef COMPILE_SHARED_LIB
	TARGET = $(addprefix $(DIR_LIBS)/, $(SHARED_LIB_NAME))
else
	TARGET = $(addprefix $(DIR_EXES)/, $(EXE))
endif

#������ͷ�ļ�����Ŀ¼
INCLUDE_DIR = $(shell find $(DIR_SRCS) -type d)
INCLUDE_DIRS =$(addprefix -I, $(INCLUDE_DIR))
#INCLUDE=$(INCLUDE_DIRS)
INCLUDE=-I./

#�����Ķ�̬��
LIBS=-lpthread

#�����ľ�̬��
STATICLIBS =

#�������
CC = gcc
CXX = g++

#���Բ���
DEBUG_OPTION = -g3 -Wall

#Ԥ�����
DEFINE_MACRO =

#���붯̬��ѡ��
ifdef COMPILE_SHARED_LIB
	SHARED_LIB_COMPILE_FLAGS = -fPIC
	SHARED_LIB_LDFLAGS = -shared -Wl,-soname,$(SHARED_LIB_NAME)
endif

#����ѡ��
CFLAGS = $(DEFINE_MACRO)
CXXFLAGS = $(DEFINE_MACRO)

#����ѡ��
LDFLAGS = $(DEFINE_MACRO) $(LIBS)

ifndef RELEASE
	CFLAGS += $(DEBUG_OPTION)
	CXXFLAGS += $(DEBUG_OPTION)
	LDFLAGS += $(DEBUG_OPTION)
endif

ifdef COMPILE_SHARED_LIB
	CFLAGS += $(SHARED_LIB_COMPILE_FLAGS)
	CXXFLAGS += $(SHARED_LIB_COMPILE_FLAGS)
	LDFLAGS += $(SHARED_LIB_LDFLAGS)
endif

#��ʱĿ���ļ�Ŀ¼
DIR_OBJS = ./tmp

#make����·��
vpath %.c $(shell find $(DIR_SRCS) -type d)
vpath %.cpp $(shell find $(DIR_SRCS) -type d)

#����,ɾ��Ŀ¼����
MKDIR = mkdir -p
RM = rm -fr

#��Ҫ������Ŀ¼
DIRS = $(DIR_OBJS) $(DIR_LIBS)

#Դ�ļ�,����·��
CSRCS = $(shell find $(DIR_SRCS) -type f -name "*.c")
CXXSRCS = $(shell find $(DIR_SRCS) -type f -name "*.cpp")

#�޳�Ŀ¼���Դ�ļ���
CSRCS_NO_DIR = $(notdir $(CSRCS))
CXXSRCS_NO_DIR = $(notdir $(CXXSRCS))

#Ŀ���ļ�
OBJS = $(CSRCS_NO_DIR:.c=.o)
OBJS += $(CXXSRCS_NO_DIR:.cpp=.o)
OBJS := $(addprefix $(DIR_OBJS)/, $(OBJS))

#����Ŀ��
all:$(DIRS) $(TARGET)

#����Ŀ¼
$(DIRS):
	$(MKDIR) $@

#����Ŀ�����
$(TARGET):$(OBJS)
	@echo "source files:" $(CSRCS) $(CXXSRCS)
	@echo "obj files:" $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LIBS) -o $@ $^ $(STATICLIBS)

#����Ŀ��
clean:
	$(RM) $(RMFLAGS) $(TARGET) $(OBJS) $(DIR_OBJS) $(DIR_LIBS)

#����Ŀ���ļ�ģʽ
$(DIR_OBJS)/%.o:%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c -o $@ $^

$(DIR_OBJS)/%.o:%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $^
