/* main.cpp
 * CSCE 463 Sample Code 
 * by Dmitri Loguinov
 */
 /*
 Caden Stewart
 CSCE 463 - Fall 2020
 */
#include "pch.h"
#include "winsock.h"

char URLs[100][256] = { "http://www.symantec.com/verisign/ssl-certificates",
"http://amti.csis.org/category/taiwan/",
"http://www.weatherline.net/",
"http://ace.wikipedia.org/wiki/%C3%94n_Keu%C3%AB",
"http://as.com/baloncesto/2015/01/01/euroliga/1420149317_950099.html",
"http://www.emirates.com/",
"http://animalresearch.wisc.edu/?attachment_id=719",
"http://allybruener.com/",
"http://youtube.com/user/USIMLS",
"http://agitprop.typepad.com/agitprop/the-power-of-the-lord/",
"http://av.voanews.com/Videoroot/Pangeavideo/2014/12/f/fc/fc287671-d5f7-443b-b6dd-9b2e48b57c79_hq.mp4?download=1",
"http://ask.arabnews.com/question/effect-emergency-vacation-contract-period/99476/law-labor",
"http://archive.wired.com/culture/?page=16",
"http://aburningpatience.blogspot.com/2012_01_01_archive.html",
"http://atr.rollcall.com/category/race-ratings/likely-republican/",
"http://arabic.cnn.com/business/2014/06/11/money-toyota-recall",
"http://alumniconnect.wagner.edu/give",
"http://advanced.jhu.edu/academics/graduate-degree-programs/museum-studies/",
"http://10plate.blog44.fc2.com/",
"http://4somaliwomen.com/index.php/component/content/article/1/937",
"http://agrumer.livejournal.com/493956.html?title=Ello&hashtags=&text=For%20those%20trying%20out%20Ello,%20%20I%E2%80%99m%20there%20as%20avram.",
"http://abigvictory.blogspot.com/search/label/Fluid",
"http://abriluno.com/doll-brothels-are-coming-to-a-city-near-you/",
"http://balkans.aljazeera.net/misljenja",
"http://allafrica.com/stories/201501020135.html",
"http://abc.go.com/shows/dancing-with-the-stars/cast/tommy-chong",
"http://1000go.blog36.fc2.com/blog-category-8.html",
"http://aisudbury.com/",
"http://ameblo.jp/19941021kusai/theme-10013164014.html",
"http://andys184.deviantart.com/art/My-desktop-2008-83926803",
"http://antilandscaper.wordpress.com/",
"http://aol.it/1bD5Mvp",
"http://abriluno.com/tag/fictional-news/",
"http://apps.cybersource.com/library/documentation/dev_guides/CC_Svcs_IG_BML_Supplement/html/",
"http://allafrica.com/stories/201501021178.html",
"http://aglifesciences.tamu.edu/careers",
"http://361107.spreadshirt.net/en/GB/Shop/Index/index",
"http://aol.sportingnews.com/nfl",
"http://art.brainpickings.org/",
"http://arts.gov/video/social-impact-design-creating-culture-storytelling-evaluation",
"http://am.globalvoicesonline.org/page/2",
"http://adv.ilsole24ore.it/RealMedia/ads/click_nx.ads/advertising.ilsole24ore.com/12/google_good_to_know/@VideoBox",
"http://atwonline.com/taxonomy/term/7392/0/feed",
"http://architectureandmorality.blogspot.com/",
"http://ba.voanews.com/media/video/2563280.html",
"http://awoiaf.westeros.org/index.php/The_Winds_of_Winter",
"http://america.aljazeera.com/topics/topic/international-location/asia-pacific/china.html",
"http://abesheet.wordpress.com/",
"http://allafrica.com/view/group/main/main/id/00034787.html",
"http://ad.doubleclick.net/jump/nbcu.rotosports/roto_home;site=roto;sect=home;!c=home;!c=noopapd!c=home;pos=1;tile=1;sz=728x90;ord=123456a?",
"http://atvs.carsoup.com/",
"http://ad.cn.doubleclick.net/jump/bottom.c.wsj.com/front;u=null**null**300x250,336x280;charset=gb2312;dcopt=ist;sz=300x250,336x280;tile=4;ord=4367059368471005?",
"http://arstechnica.com/science",
"http://astrecords.bigcartel.com/products",
"http://balkans.aljazeera.net/vijesti/mjesecno-porodici-u-srbiji-treba-1000-eura",
"http://balkin.blogspot.com/2006/10/yes-its-no-brainer-waterboarding-is.html?showComment=1162066560000",
"http://aperture.org/shop/larry-towell-afghanistan-books",
"http://alantonelson.wordpress.com/",
"http://adindex.laweekly.com/palm-tree-l-a--69849/2350745",
"http://adswithoutproducts.com/category/handke/",
"http://associatesmind.com/category/site-news-2/uncategorized/",
"http://1ddreamgirlposts.tumblr.com/tagged/style",
"http://airforce.com/parents-family/deployment/",
"http://4vector.deviantart.com/art/eGo-c-Twist-Preview-424667979",
"http://ar.globalvoicesonline.org/author/ibtehal-algohary/",
"http://360.ch/blog/magazine/2014/08/cadeaux-fiscaux-aux-guerisseurs-de-gays/",
"http://1000go.blog36.fc2.com/blog-category-6.html",
"http://awoiaf.westeros.org/index.php/Della_Frey",
"http://adobeevent.bizcom.com.cn/edm/20140930/DPS_Shanghai_CN-gdcbanner.htm",
"http://admissions.cornell.edu/learn/academics",
"http://animalscience.tamu.edu/event/introductory-haccp-developing-and-implementing-haccp-plans-4/",
"http://ar.wikinews.org/wiki/%D9%85%D9%84%D9%81:Tomboy_logo.svg",
"http://assembly.coe.int/main.asp?Link=/documents/adoptedtext/ta07/eres1577.htm",
"http://architecturaldigest.com/",
"http://alphanow.thomsonreuters.com/membership-registration/",
"http://action.mediamatters.org/local-fox-stations",
"http://archive.wired.com/cars/?page=16",
"http://alloyentertainment.com/authors/elena-perez/",
"http://allafrica.com/view/group/main/main/id/00034468.html",
"http://b.hatena.ne.jp/search/tag?q=%E3%82%A2%E3%83%97%E3%83%AA",
"http://archive.wired.com/cars/?page=37",
"http://9to5toys.com/2014/12/18/audio-technica-sonicpro-ckr-new-headphones/",
"http://ansarov.com/",
"http://cuiyi.org/",
"http://akronohio.planetdiscover.com/sp?skin=&aff=1109&catId=20000000",
"http://archive.fiba.com/pages/eng/fa/team/p/sid/8743/tid/282/_/2013_EuroBasket_Women/index.html",
"http://apartments.about.com/b/2014/05/23/a-heartfelt-thanks-to-my-readers.htm",
"http://angelmontes.my4life.com/",
"http://agrilifeextension.tamu.edu/programs/volunteer-programs/",
"http://abigvictory.blogspot.com/search/label/Turnersville",
"http://ad.doubleclick.net/N617/jump/defenseone.com/topic_middle-east;pos=river-ad;sz=300x150;",
"http://all-that-is-interesting.com/australia-extreme-weather",
"http://artsandsciences.osu.edu/about/administration",
"http://am.globalvoicesonline.org/-/topics/economics-business",
"http://balkans.aljazeera.net/tag/ivan-vrdoljak",
"http://archive.wired.com/reviews/productlisting/gaming_gear",
"http://agitprop.typepad.com/agitprop/2009/08/index.html",
"http://aburningpatience.blogspot.com/2006/05/reading-denise-levertov-again.html",
"http://appleseeds.blair.com/t/sale/997-under/pc/69/2664.uts?count=12&i=1&intl=n&q=*&q1=69%7ESale&q2=2664%7E$9.97+%26+Under&q3=2X&rank=rank&sc=Y&store=1&x1=c.t1&x2=c.t2&x3=s.sizenormal",
"http://althouse.blogspot.com/2006_01_01_archive.html"
}; //list of URLs for bulk testing (didn't want to make a shell script)

// this class is passed to all threads, acts as shared memory
class Parameters {
public:
	HANDLE	mutex;
	HANDLE	finished;
	HANDLE	eventQuit;
};

// this function is where threadA starts
UINT threadA (LPVOID pParam)
{
	Parameters *p = ((Parameters*)pParam);

	// wait for mutex, then print and sleep inside the critical section
	WaitForSingleObject (p->mutex, INFINITE);					// lock mutex
	printf ("threadA %d started\n", GetCurrentThreadId ());		// print inside critical section to avoid screen garbage
	Sleep (1000);												// sleep 1 second
	ReleaseMutex (p->mutex);									// release critical section

	// signal that this thread has finished its job
	ReleaseSemaphore (p->finished, 1, NULL);

	// wait for threadB to allow us to quit
	WaitForSingleObject (p->eventQuit, INFINITE);

	// print we're about to exit
	WaitForSingleObject (p->mutex, INFINITE);					
	printf ("threadA %d quitting on event\n", GetCurrentThreadId ());		
	ReleaseMutex (p->mutex);										

	return 0;
}

// this function is where threadB starts
UINT threadB (LPVOID pParam)
{
	Parameters *p = ((Parameters*)pParam);

	// wait for both threadA threads to quit
	WaitForSingleObject (p->finished, INFINITE);
	WaitForSingleObject (p->finished, INFINITE);

	printf ("threadB woken up!\n");				// no need to sync as only threadB can print at this time
	Sleep (3000);

	printf ("threadB setting eventQuit\n"); 	// no need to sync as only threadB can print at this time

	// force other threads to quit
	SetEvent (p->eventQuit);

	return 0;
}

using namespace std;

int main(int argc, char* argv[])
{
	// connect to a server; test basic winsock functionality

	ifstream inFile;
	istringstream fileReadIn;
	long long lineCount = 0;
	long long charIndex = 0;
	char** URLs;
	ostringstream output;
	string s, fileData;
	char URL[MAX_URL_LEN] = { NULL };

	switch (argc) {
	case 1:
		printf("No argument was given!");
		break;
	case 2:
		winsock_test(argv[1]);
		break;
	case 3:
		//thread stuf
		inFile.open(argv[2], ios::in | ios::binary);
		output << inFile.rdbuf();
		fileData = output.str();
		inFile.close();

		while (fileData[charIndex] != '\0') {
			if (fileData[charIndex] == '\n')
				lineCount++;
			charIndex++;
		}

		URLs = new char*[lineCount];

		fileReadIn = istringstream(fileData);
		for (int i = 0; i < lineCount; i++) { //easy manipulation, the 1M URL doesn't take up too much memory
			getline(fileReadIn, s);
			s.pop_back(); //get rid of carriage return 
		
			URLs[i] = s.c_str();
			winsock_test(s);
		}

		break;
	default:
		printf("Invalid input, ");
		if (argc < 2) {
			printf("not enough arguments!");
		}
		else if (argc > 3) {
			printf("too many arguments!");
		}
		return -1;
	}
	
	/*for (int i = 0; i < 100; i++) { //tests all the urls
		winsock_test(URLs[i]);
	}*/

	

	
	
	/*// print our primary/secondary DNS IPs
	DNS dns;
	dns.printDNSServer ();

	printf ("-----------------\n");

	CPU cpu;
	// run a loop printing CPU usage 10 times
	for (int i = 0; i < 10; i++)
	{
		// average CPU utilization over 200 ms; must sleep at least a few milliseconds *after* the constructor 
		// of class CPU and between calls to GetCpuUtilization
		Sleep (200);
		// now print
		double util = cpu.GetCpuUtilization (NULL);
		// -2 means the kernel counters did not accumulate enough to produce a result
		if (util != -2)
			printf ("current CPU utilization %f%%\n", util);
	}

	printf ("-----------------\n");

	// thread handles are stored here; they can be used to check status of threads, or kill them
	HANDLE *handles = new HANDLE [3];
	Parameters p;
	
	// create a mutex for accessing critical sections (including printf); initial state = not locked
	p.mutex = CreateMutex (NULL, 0, NULL);	
	// create a semaphore that counts the number of active threads; initial value = 0, max = 2
	p.finished = CreateSemaphore (NULL, 0, 2, NULL);
	// create a quit event; manual reset, initial state = not signaled
	p.eventQuit = CreateEvent (NULL, true, false, NULL);

	// get current time; link with winmm.lib
	clock_t t = clock();

	// structure p is the shared space between the threads
	handles [0] = CreateThread (NULL, 0, (LPTHREAD_START_ROUTINE)threadA, &p, 0, NULL);		// start threadA (instance #1) 
	handles [1] = CreateThread (NULL, 0, (LPTHREAD_START_ROUTINE)threadA, &p, 0, NULL);		// start threadA (instance #2)
	handles [2] = CreateThread (NULL, 0, (LPTHREAD_START_ROUTINE)threadB, &p, 0, NULL);		// start threadB 

	// make sure this thread hangs here until the other three quit; otherwise, the program will terminate prematurely
	for (int i = 0; i < 3; i++)
	{
		WaitForSingleObject (handles [i], INFINITE);
		CloseHandle (handles [i]);
	}
	
	printf ("terminating main(), completion time %.2f sec\n", (double)(clock() - t)/CLOCKS_PER_SEC);
	return 0; */
}
