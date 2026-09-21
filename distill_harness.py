#!/usr/bin/env python3
import time
import random
import asyncio

class RateLimiter:
    def __init__(self, rpm):
        self.rpm = rpm
        self.interval = 60.0 / rpm
        self.last_call = 0

    async def wait(self):
        now = time.time()
        elapsed = now - self.last_call
        if elapsed < self.interval:
            await asyncio.sleep(self.interval - elapsed)
        self.last_call = time.time()

async def query_provider(lane_id, provider, model, rate_limiter):
    backoff_exp = 1

    while True:
        await rate_limiter.wait()

        # Simulate network failure / 429
        if random.random() < 0.05:
            sleep_time = 3 ** backoff_exp
            print(f"[Lane {lane_id}] [{provider}] HTTP 429 - Backing off for {sleep_time}s")
            await asyncio.sleep(sleep_time)
            backoff_exp = min(backoff_exp + 1, 3) # Max 27s
            continue

        backoff_exp = 1 # Reset on success

        # Simulate generating coordinates
        coords = [random.choice([-1, 0, 1]) for _ in range(11)]
        return coords

async def lane_worker(lane_id, provider, models, rpm):
    limiter = RateLimiter(rpm)
    while True:
        model = random.choice(models)
        coords = await query_provider(lane_id, provider, model, limiter)
        # In a real system, we write coords to /dev/shm/ternary_stream here
        await asyncio.sleep(0.1)

async def main():
    print("[*] Starting 30-Lane Hybrid Fleet Distillation Harness")

    lanes = []

    # 10 Google Lanes
    for i in range(10):
        lanes.append(lane_worker(i, "Google", ["gemini-3.8-flash", "gemini-3.7-flash"], 60))

    # 10 NVIDIA Lanes (40 RPM saturation target)
    for i in range(10, 20):
        lanes.append(lane_worker(i, "NVIDIA", ["GLM-5-3", "kimi-k3"], 4))

    # 10 Groq Lanes
    for i in range(20, 30):
        lanes.append(lane_worker(i, "Groq", ["GPTOSS 120B"], 120))

    print("[+] All lanes initialized. Distilling...")

    # Run for 5 seconds as a stub
    try:
        await asyncio.wait_for(asyncio.gather(*lanes), timeout=5.0)
    except asyncio.TimeoutError:
        print("[+] Distillation simulation complete.")

if __name__ == "__main__":
    asyncio.run(main())
