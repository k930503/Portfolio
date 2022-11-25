using UnityEngine;

public class AudioManager : MonoBehaviour
{
    AudioSource playerAudioSource;
    public AudioSource bgmAudioSource; // bgm 틀어줄 audio source

    public enum BGM { DAY = 0, NIGHT = 1 }
	[Header("Day & Night Clips")]
	public AudioClip[] bgm;
	[Space]

    [SerializeField] AudioClip playerDeathMusic;

    [SerializeField] AudioClip clickSound;
    [SerializeField] AudioClip craftingSuccess;
    [SerializeField] AudioClip craftingFailure;

    public delegate void ChangeSFXVolume();
    public event ChangeSFXVolume OnSFXVolumeChanged;
    public delegate void ChangeBGMVolume();
    public event ChangeBGMVolume OnBGMVolumeChanged;

    #region 싱글톤
    private static AudioManager instance = null;
    public static AudioManager Instance
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

    private void Start()
    {
        bgmAudioSource.volume = DataManagement.DataManager.Instance.BGMVolume;
        EarthRevolution.Instance.OnSwitchedTime += TurnOnBGM;
        TurnOnBGM();

        playerAudioSource = GameManager.Instance.Player.GetComponent<AudioSource>();
    }

    private void TurnOnBGM()
    {
        if (EarthRevolution.Instance.IsNightTime)
        {
			bgmAudioSource.clip = bgm[(int)BGM.NIGHT];
			bgmAudioSource.Play();       
        }
        else
        {
            bgmAudioSource.clip = bgm[(int)BGM.DAY];
            bgmAudioSource.Play();
        }
    }

    public void ClickSFX()
    {
        playerAudioSource.PlayOneShot(clickSound);
    }

    public void SucceededInCrafting()
    {
        playerAudioSource.PlayOneShot(craftingSuccess);
    }

    public void FailedToCraft()
    {
        playerAudioSource.PlayOneShot(craftingFailure);
    }

    public void TurnOnDeathBGM()
    {
        bgmAudioSource.PlayOneShot(playerDeathMusic);
    }

    public void BGMVolumeChange()
    {
        bgmAudioSource.volume = DataManagement.DataManager.Instance.BGMVolume;

        if(OnBGMVolumeChanged != null)
        {
            OnBGMVolumeChanged();
        }
    }

    public void SFXVolumeChange()
    {
        playerAudioSource.volume = DataManagement.DataManager.Instance.SFXVolume;

        if (OnSFXVolumeChanged != null)
        {
            OnSFXVolumeChanged();
        }
    }
}
