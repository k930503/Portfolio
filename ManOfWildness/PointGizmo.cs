using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PointGizmo : MonoBehaviour
{
	public bool isSpawn = false;
	public enum Habitat { Water = 0, Ground = 1 }
	public Habitat habitat = Habitat.Ground;
	public enum GizmoType
	{
		SPAWN_POINT,
		WAY_POINT
	}
	public GizmoType type;

	public Color choiceColor;
	float radius = 5.0f;

	public string pointFile;


	private void OnDrawGizmos()
	{
		int layerMask;
		if(habitat == Habitat.Ground)
		{
			layerMask = 1 << LayerMask.NameToLayer("Ground");
		}
		else
		{
			layerMask = 1 << LayerMask.NameToLayer("WaterPlane");
		}

		float rayRange = 2800.0f;

		// 기즈모 색상 설정
		Gizmos.color = choiceColor;

		RaycastHit hit;

		if (Physics.Raycast(transform.position, -transform.up, out hit, rayRange, layerMask) || Physics.Raycast(transform.position, transform.up, out hit, rayRange, layerMask))
		{
			Debug.DrawRay(transform.position, -transform.up, Color.green, 0.5f, true);
			//transform.position = new Vector3(transform.position.x, hit.point.y, transform.position.z);
		}
		if (type == GizmoType.SPAWN_POINT)
        {
            Gizmos.DrawIcon(transform.position + Vector3.up * 1.0f, pointFile, false);
        }
        else
        {
            // 구체 모양의 기즈모 생성, 파라미터는 1.생성위치, 2.반지름
            Gizmos.DrawSphere(transform.position, radius);
        }
    }
}
