using System;
using System.IO;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[Serializable]
public class State
{
	public string name;
	public int hp;
	public int power;
	public int walkSpeed;
	public int runSpeed;
	public int viewRange;
	public int viewAngle;
	public int minimumItemDropCount;
	public int maximumItemDropCount;
}

[Serializable]
public class AnimalTableData {

	const string tableDataPath = "Assets/13. Data/TableData.json";
	public List<State> objectStates = new List<State>();
	public Dictionary<string, State> states = new Dictionary<string, State>();

	public static AnimalTableData LoadTableData()
	{
#if UNITY_EDITOR
		string jsonString = File.ReadAllText(tableDataPath);
#else
		TextAsset asset = Resources.Load("Texts/TableData") as TextAsset;
		string jsonString = asset.text;

#endif
		AnimalTableData tableData = JsonUtility.FromJson<AnimalTableData>(jsonString);
		tableData.GenerateStates();
		return tableData;
	}

	public void GenerateStates()
	{
		foreach(var state in objectStates)
		{
			states.Add(state.name, state);
		}
	}
}
