﻿//------------------------------------------------------------------------------
// <auto-generated>
//     此代码由工具生成
//     如果重新生成代码，将丢失对此文件所做的更改。
// </auto-generated>
//------------------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

public class Machine
{
	public virtual Point5D m_MachinePos
	{
		get;
		set;
	}

	public virtual MachineState m_MachineState
	{
		get;
		set;
	}

	public virtual QVector <float> m_NozzleTemp
	{
		get;
		set;
	}

	public virtual float m_PlatformTemp
	{
		get;
		set;
	}

	public virtual void SetMachineState(object MachineState state)
	{
		throw new System.NotImplementedException();
	}

	public virtual MachineState GetMachineState()
	{
		throw new System.NotImplementedException();
	}

	public virtual void SetMachinePos(object CPoint5D & p)
	{
		throw new System.NotImplementedException();
	}

}

