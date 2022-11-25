using UnityEngine;
using UnityEngine.EventSystems;

public class DraggingWindow : MonoBehaviour, IPointerDownHandler, IDragHandler {

    private Vector2 pointerOffSet; // 마우스포인터가 클릭된 지점의 좌표를 저장할 변수
    [SerializeField] RectTransform canvasRectTransform;  // Canvas의 Rect Transform
    [SerializeField] RectTransform windowRectTransform;  // 드래그되는 창의 Rect Transform


    public void OnPointerDown(PointerEventData eventData) 
    {
        RectTransformUtility.ScreenPointToLocalPointInRectangle(windowRectTransform, eventData.position, eventData.pressEventCamera, out pointerOffSet); // RectTransform의 로컬좌표를 계산    
    }

    public void OnDrag(PointerEventData eventData)
    {
        Vector2 pointerPositionTobeDragged;
        if(RectTransformUtility.ScreenPointToLocalPointInRectangle(canvasRectTransform, Input.mousePosition, eventData.pressEventCamera, out pointerPositionTobeDragged))
        {
            windowRectTransform.localPosition = pointerPositionTobeDragged - pointerOffSet;
        }
    }            		
}
