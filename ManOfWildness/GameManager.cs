using UnityEngine;
using UnityEngine.SceneManagement;

public class GameManager : MonoBehaviour
{
    public GameObject animalBloodEffect;
	public GameObject skeletonPrefab;
	public GameObject meatPickupPrefab;
	public GameObject campFire;

    private Inventory inventory;
    public Inventory Inventory
    {
        get
        {
            return inventory;
        }
    }
    private ConsumePanel consumePanel;
    public ConsumePanel ConsumePanel
    {
        get
        {
            return consumePanel;
        }
    }

    private GameObject player;
    public GameObject Player
    {
        get
        {
            return player;
        }
    }
 
    bool newGame = false;
    public bool NewGame
    {
        get
        {
            return newGame;
        }

        set
        {
            newGame = value;
        }
    }

	#region 싱글톤
	private static GameManager instance = null;
	public static GameManager Instance
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
            DontDestroyOnLoad(gameObject);

            FindPlayer();    // TODO 나중에 지우기. 디버깅용
            FindInventory(); // TODO 나중에 지우기. 디버깅용
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
        SceneManager.sceneLoaded += OnNewSceneLoaded;  // 씬 전환될때 실행시킬 함수 추가
    }

    public void OnNewSceneLoaded(Scene scene, LoadSceneMode mode)
    {
        Debug.Log("New Scene Has been Loaded");
        FindPlayer();       // 메인메뉴씬에서 -> 플레이씬으로 씬전환하자마자 플레이어 가져오기
        FindInventory();    // 메인메뉴씬에서 -> 플레이씬으로 씬전환하자마자 플레이어 가져오기
    }

    void FindPlayer()
    {
        player = GameObject.FindGameObjectWithTag("Player");
    }

    void FindInventory()
    {
        if(SceneManager.GetActiveScene().buildIndex != 0) // TODO 임시코드.. 빌드할때 수정하기
        {
            GameObject playScreen = GameObject.FindGameObjectWithTag("PlayScreen");
            inventory = playScreen.GetComponentInChildren<Inventory>();
            consumePanel = playScreen.GetComponentInChildren<ConsumePanel>();
        }
    }

    // 플레이 도중 메인메뉴로 돌아가기
    public void LoadMainMenu()
	{
		SceneManager.LoadScene("MainMenu");
	}

    // 다음씬으로 전환해주는 함수
    public void LoadNextScene()
    {
        int currentSceneIdx = SceneManager.GetActiveScene().buildIndex;
        int totalSceneIdx = SceneManager.sceneCountInBuildSettings;
        SceneManager.LoadScene((currentSceneIdx + 1) % totalSceneIdx);
    }
}
