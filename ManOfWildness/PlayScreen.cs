using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PlayScreen : MonoBehaviour {

	[SerializeField] CanvasGroup gameOptionCG;
	[SerializeField] CanvasGroup inventoryCG;
	[SerializeField] CanvasGroup craftingCG;
    [SerializeField] CanvasGroup gameSettingCG;

    [SerializeField] Transform compassDirTransform;
    [SerializeField] Animator fadeInOutAnimator;

    [SerializeField] Slider bgmVolumeSlider;
    [SerializeField] Slider sfxVolumeSlider;
    [SerializeField] Dropdown graphicDropDown;
    [SerializeField] Toggle fullScreenToggle;
    [SerializeField] Dropdown resolutionDropDown;

    Resolution[] resolutions;

	public GameObject arrowCover;

    public Image bloodScreen;

	bool gameOptionToggle = false;
	bool inventoryToggle = false;
	bool craftingToggle = false;
    bool gameSettingToggle = false;

	Transform playerTransform; 
	Vector3 dir = Vector3.zero;
    

	private void Start()
	{
		playerTransform = GameManager.Instance.Player.transform;       
        InitializePlayScreen();     
    }

	private void InitializePlayScreen()
	{
        inventoryCG.alpha = inventoryToggle ? 1.0f : 0.0f;
        inventoryCG.interactable = inventoryToggle;
        inventoryCG.blocksRaycasts = inventoryToggle;

		craftingCG.alpha = craftingToggle ? 1.0f : 0.0f;
		craftingCG.interactable = craftingToggle;
		craftingCG.blocksRaycasts = craftingToggle;

		gameOptionCG.alpha = gameOptionToggle ? 1.0f : 0.0f;
		gameOptionCG.interactable = gameOptionToggle;
		gameOptionCG.blocksRaycasts = gameOptionToggle;

        gameSettingCG.alpha = gameSettingToggle ? 1.0f : 0.0f;
        gameSettingCG.interactable = gameSettingToggle;
        gameSettingCG.blocksRaycasts = gameSettingToggle;

        resolutions = Screen.resolutions;
        resolutionDropDown.ClearOptions();
        List<string> options = new List<string>();
        int currentResolutionIndex = 0;

        for (int i = 0; i < resolutions.Length; i++)
        {
            string option = resolutions[i].width + " x " + resolutions[i].height;
            options.Add(option);

            if(resolutions[i].width == Screen.currentResolution.width && resolutions[i].height == Screen.currentResolution.height)
            {
                currentResolutionIndex = i;
            }
        }
        resolutionDropDown.AddOptions(options);
        resolutionDropDown.value = currentResolutionIndex;
        resolutionDropDown.RefreshShownValue();
    }


    // 인벤토리 창 버튼 클릭했을 때 호출할 함수
	public void OnInventoryButtonClicked()
	{
        inventoryToggle = !inventoryToggle;
        inventoryCG.alpha = inventoryToggle ? 1.0f : 0.0f;
        inventoryCG.interactable = inventoryToggle;
        inventoryCG.blocksRaycasts = inventoryToggle;

        AudioManager.Instance.ClickSFX();
    }

    // 크래프팅 창 버튼 클릭했을 때 호출할 함수
	public void OnCraftingButtonClicked()
	{
		craftingToggle = !craftingToggle;
		craftingCG.alpha = craftingToggle ? 1.0f : 0.0f;
		craftingCG.interactable = craftingToggle;
		craftingCG.blocksRaycasts = craftingToggle;

        AudioManager.Instance.ClickSFX();
    }

    // 우측 상단 게임옵션 Cog버튼 클릭했을 때 호출할 함수
	public void OnGameOptionButtonClicked()
	{
		gameOptionToggle = !gameOptionToggle;
		gameOptionCG.alpha = gameOptionToggle ? 1.0f : 0.0f;
		gameOptionCG.interactable = gameOptionToggle;
		gameOptionCG.blocksRaycasts = gameOptionToggle;

        AudioManager.Instance.ClickSFX();
    }

    // 게임옵션-게임셋팅 클릭했을 때 호출할 함수
    public void OnGameSettingClikced()
    {
        gameSettingToggle = !gameSettingToggle;
        gameSettingCG.alpha = gameSettingToggle ? 1.0f : 0.0f;
        gameSettingCG.interactable = gameSettingToggle;
        gameSettingCG.blocksRaycasts = gameSettingToggle;

        if(gameSettingToggle)
        {
            bgmVolumeSlider.value = DataManagement.DataManager.Instance.BGMVolume;
            sfxVolumeSlider.value = DataManagement.DataManager.Instance.SFXVolume;
            graphicDropDown.value = QualitySettings.GetQualityLevel();
            fullScreenToggle.isOn = Screen.fullScreen;
        }

        AudioManager.Instance.ClickSFX();
    }

    // 게임셋팅 창에서 BGM볼륨변경했을 때 호출할 함수
    public void OnBGMVolumeChanged(float volume)
    {
        DataManagement.DataManager.Instance.BGMVolume = volume;
        if (DataManagement.DataManager.Instance != null)
        {
            DataManagement.DataManager.Instance.Save();
        }

        AudioManager.Instance.BGMVolumeChange(); // 이벤트 호출
    }

    // 게임셋팅 창에서 SFX볼륨변경했을 때 호출할 함수
    public void OnSFXVolumeChanged(float volume)
    {
        DataManagement.DataManager.Instance.SFXVolume = volume;
        if (DataManagement.DataManager.Instance != null)
        {
            DataManagement.DataManager.Instance.Save();
        }

        AudioManager.Instance.SFXVolumeChange();
    }

    // 게임셋팅 창에서 풀스크린 토글했을 때 호출할 함수
    public void FullScreen(bool isFullScreen)
    {
        Screen.fullScreen = isFullScreen; // 이벤트 호출
    }

    // 게임셋팅 창에서 Resolution값 변경할 때 호출할 함수
    public void SetResolution(int resolutionIndex)
    {
        Resolution resolution = resolutions[resolutionIndex];
        Screen.SetResolution(resolution.width, resolution.height, Screen.fullScreen);
    }

    // 게임셋팅 창에서 그래픽퀄리티 옵션 변경할 때 호출할 함수
    public void GraphicSetting(int qualityIndex)
    {
        QualitySettings.SetQualityLevel(qualityIndex);
    }

    public void OnSaveButtonClicked()
    {
        GameSaver.Instance.SaveGame();
    }

    public void OnQuitButtonClicked()
    {
        fadeInOutAnimator.SetTrigger("fadeOut");
    }

    // 매프레임 나침반 회전시켜주기
	void Update()
	{      
        dir.z = playerTransform.eulerAngles.y;
        compassDirTransform.localEulerAngles = dir;

        if(Input.GetKeyDown(KeyCode.I))
        {
            OnInventoryButtonClicked();
            if(inventoryToggle)
            {
                if (CursorManager.Instance.CursorLocked)
                {
                    CursorManager.Instance.CursorLocked = false;
                    CursorManager.Instance.ToggleCursorLock();
                }
            }
        }
	}
}
