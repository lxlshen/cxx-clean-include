///<------------------------------------------------------------------------------
//< @file:   project.h
//< @author: 洪坤安
//< @date:   2016年3月7日
//< @brief:
//< Copyright (c) 2016. All rights reserved.
///<------------------------------------------------------------------------------

#ifndef _project_h_
#define _project_h_

#include <string>
#include <set>
#include <vector>

enum VerboseLvl
{
	VerboseLvl_1 = 1,	// 仅打印各文件的清理情况
	VerboseLvl_2,		// 用于调试：打印各文件引用到了其他文件的类名、函数名、宏名
	VerboseLvl_3,		// 用于调试：打印各文件直接或者间接依赖的文件集
	VerboseLvl_4,		// 用于调试：打印c++文件列表
	VerboseLvl_5,		// 用于调试：打印异常
	VerboseLvl_Max
};

// 项目配置
class Project
{
public:
	Project()
		: m_isDeepClean(false)
		, m_onlyHas1File(false)
		, m_isOverWrite(false)
		, m_verboseLvl(0)
	{
	}

public:
	// 该文件是否允许被清理
	bool CanClean(const std::string &filename) const
	{
		return CanClean(filename.c_str());
	}

	// 该文件是否允许被清理
	bool CanClean(const char* filename) const;

	// 生成允许清理文件列表
	void GenerateAllowCleanList();

	// 移除非c++后缀的源文件
	void Fix();

	// 打印本次清理的文件列表
	void Print() const;

public:
	static Project instance;

public:
	// 允许被清理的文件夹（只有处于该文件夹下的c++文件才允许被改动）
	std::string					m_allowCleanDir;

	// 允许被清理的文件列表（只有属于本列表内的c++文件才允许被改动），注意：当允许清理文件夹不为空时，本项无意义
	std::set<std::string>		m_allowCleanList;	

	// 待清理的c++源文件列表，只能是c++后缀的文件，如cpp、cxx等
	std::vector<std::string>	m_cpps;

	// 工作目录
	std::string					m_workingDir;

	// 命令行选项：是否深层清理，建议为true
	bool						m_isDeepClean;

	// 命令行选项：是否只有一个文件（当只有一个文件时，只需要解析一次）
	bool						m_onlyHas1File;	

	// 命令行选项：是否覆盖原来的c++文件（当本选项被关闭时，项目内的c++文件不会有任何改动）
	bool						m_isOverWrite;

	// 命令行选项：打印的详细程度，0 ~ 9，0表示不打印，默认为1，最详细的是9
	int							m_verboseLvl;
};

#endif // _project_h_