import urllib.request
import json
import time

def fetch_tide_data():
    # NOAA Tides & Currents API
    # Station 8518750 (The Battery, NY)
    # Datum: MLLW (Mean Lower Low Water)
    url = "https://api.tidesandcurrents.noaa.gov/api/prod/datagetter?product=water_level&station=8518750&date=latest&datum=MLLW&units=english&time_zone=lst_ldt&format=json"
    
    print(f"Fetching: {url}")
    
    try:
        with urllib.request.urlopen(url) as response:
            data = json.loads(response.read().decode())
            
        if 'error' in data:
            print("API Error:", data['error'])
            return None
            
        # Example response: {"data": [{"t": "2024-01-20 12:00", "v": "2.541", "s": "0.012", "f": "1,0,0,0", "q": "p"}]}
        observation = data['data'][0]
        water_level = float(observation['v'])
        time_str = observation['t']
        
        print(f"--- NOAA Tide Data ---")
        print(f"Station: The Battery, NY")
        print(f"Time: {time_str}")
        print(f"Water Level: {water_level} ft (MLLW)")
        
        # Normalize to 0-1 (assuming range -2 to 8 ft for typical tidal swing)
        min_tide = -2.0
        max_tide = 8.0
        normalized = (water_level - min_tide) / (max_tide - min_tide)
        normalized = max(0.0, min(1.0, normalized))
        
        print(f"Normalized Value: {normalized:.4f}")
        return normalized

    except Exception as e:
        print(f"Fetch Failed: {e}")
        return None

if __name__ == "__main__":
    fetch_tide_data()
