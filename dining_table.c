
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
typedef HANDLE thread_t;
typedef HANDLE semaphore_t;
#define THREAD_RETURN DWORD WINAPI
#define THREAD_RESULT 0

static int semaphore_init(semaphore_t *sem)
{
    *sem = CreateSemaphoreA(NULL, 1, 1, NULL);
    return *sem == NULL ? -1 : 0;
}

static void semaphore_wait(semaphore_t *sem)
{
    WaitForSingleObject(*sem, INFINITE);
}

static void semaphore_post(semaphore_t *sem)
{
    ReleaseSemaphore(*sem, 1, NULL);
}

static void semaphore_destroy(semaphore_t *sem)
{
    CloseHandle(*sem);
}

static void sleep_seconds(unsigned int seconds)
{
    Sleep(seconds * 1000);
}

static thread_t thread_create(THREAD_RETURN (WINAPI *function)(void *), void *arg)
{
    return CreateThread(NULL, 0, function, arg, 0, NULL);
}

static void thread_join(thread_t thread)
{
    WaitForSingleObject(thread, INFINITE);
    CloseHandle(thread);
}
#else
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
typedef pthread_t thread_t;
typedef sem_t semaphore_t;
#define THREAD_RETURN void *
#define THREAD_RESULT NULL

static int semaphore_init(semaphore_t *sem) { return sem_init(sem, 0, 1); }
static void semaphore_wait(semaphore_t *sem) { sem_wait(sem); }
static void semaphore_post(semaphore_t *sem) { sem_post(sem); }
static void semaphore_destroy(semaphore_t *sem) { sem_destroy(sem); }
static void sleep_seconds(unsigned int seconds) { sleep(seconds); }

static thread_t thread_create(THREAD_RETURN (*function)(void *), void *arg)
{
    thread_t thread;
    pthread_create(&thread, NULL, function, arg);
    return thread;
}

static void thread_join(thread_t thread) { pthread_join(thread, NULL); }
#endif

#define N 5

semaphore_t fork[N];

// Philosopher function
THREAD_RETURN philosopher(void* num)
{
    int id = *(int*)num;

    while(1)
    {
        printf("\nPhilosopher %d is thinking", id);
        sleep_seconds(1);

        // Pick up left fork
        semaphore_wait(&fork[id]);

        // Pick up right fork
        semaphore_wait(&fork[(id + 1) % N]);

        // Eating
        printf("\nPhilosopher %d is eating", id);
        sleep_seconds(2);

        // Put down left fork
        semaphore_post(&fork[id]);

        // Put down right fork
        semaphore_post(&fork[(id + 1) % N]);

        printf("\nPhilosopher %d finished eating\n", id);
    }

    return THREAD_RESULT;
}

int main()
{
    thread_t thread[N];
    int id[N];

    // Initialize all forks
    for(int i = 0; i < N; i++)
    {
        semaphore_init(&fork[i]);
    }

    // Create philosopher threads
    for(int i = 0; i < N; i++)
    {
        id[i] = i;
        thread[i] = thread_create(philosopher, &id[i]);
    }

    // Wait for threads
    for(int i = 0; i < N; i++)
    {
        thread_join(thread[i]);
    }

    // Destroy semaphores
    for(int i = 0; i < N; i++)
    {
        semaphore_destroy(&fork[i]);
    }

    return 0;
}
