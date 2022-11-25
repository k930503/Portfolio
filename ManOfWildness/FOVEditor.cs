using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//Editor 클래스에 접근하기 위해 명시해야 하는 네임스페이스
using UnityEditor;

[CustomEditor(typeof(AnimalFOV))]
public class FOVEditor : Editor {

    private void OnSceneGUI()
    {
        //AnimalFOV 클래스를 참조
        AnimalFOV fov = (AnimalFOV)target;
		AnimalState animalState = fov.gameObject.GetComponent<AnimalState>();

        //원주 위의 시작점의 좌표를 계산(주어진 각도의 1/2)
        Vector3 fromAnglePos = fov.CirclePoint(-animalState.viewAngle * 0.5f);

        //원의 색상을 흰색으로 지정
        Handles.color = Color.white;

        //외각선만 표현하는 원반을 그림
        Handles.DrawWireDisc(fov.transform.position, Vector3.up, animalState.viewRange); // 원점 좌표, 노멀 벡터, 원의 반지름

        //부채꼴의 색상을 지정
        Handles.color = new Color(1, 1, 1, 0.2f);

        //채워진 부채꼴을 그림
        Handles.DrawSolidArc(fov.transform.position, Vector3.up, fromAnglePos, animalState.viewAngle, animalState.viewRange); //원점 좌표, 노멀 벡터, 부채꼴의 시작좌표, 부채꼴의 각도, 부채꼴의 반지름

        //시야각의 텍스트를 표시
        Handles.Label(fov.transform.position + (fov.transform.forward * 2.0f), animalState.viewAngle.ToString());

    }
}
