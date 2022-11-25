using System.Collections;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class PlaySceneLoader : MonoBehaviour {

    Slider slider;
    Text percentageText;
    [SerializeField] GameObject cam;
    [SerializeField] Transform loadingCameraTransform;

    #region 싱글톤
    private static PlaySceneLoader instance = null;
    public static PlaySceneLoader Instance
    {
        get
        {
            return instance;
        }
    }

    private void Awake()
    {
        if (instance == null)
        {
            instance = this;
            cam = Camera.main.gameObject;
        }
        else
        {
            Destroy(gameObject);
        }
    }

    private void OnDestroy()
    {
        if (instance == this)
        {
            instance = null;
        }
    }
    #endregion

    // 메인메뉴화면에서 플레이 씬을 로드해주는 함수
    public void LoadPlayScene(int sceneIdx, Slider s, Text t)
    {
        slider = s;
        percentageText = t;
        StartCoroutine(LoadAsynchronously(sceneIdx));
    }

    IEnumerator LoadAsynchronously(int sceneIdx)
    {
        AsyncOperation operation = SceneManager.LoadSceneAsync(sceneIdx);

        while (!operation.isDone)
        {
            cam.transform.position = Vector3.Lerp(cam.transform.position,
                                   loadingCameraTransform.position, Time.deltaTime);
            cam.transform.rotation = Quaternion.Lerp(cam.transform.rotation,
                                   loadingCameraTransform.rotation, Time.deltaTime);

            float progress = Mathf.Clamp01(operation.progress / 0.9f);
            slider.value = progress;
            percentageText.text = Mathf.Round(progress * 100.0f) + "%";

            yield return null;
        }
    }
}
