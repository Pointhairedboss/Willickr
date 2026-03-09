import os
import time
import requests
from bs4 import BeautifulSoup
from urllib.parse import urljoin, urlparse
import markdownify

INDEX_URL = "https://forum.audulus.com/t/sound-on-sound-synth-secrets-by-gordon-reid/74"
BASE_DIR = os.path.join(os.getcwd(), "SyntheoryGordonReid")
IMG_DIR = os.path.join(BASE_DIR, "images")

os.makedirs(IMG_DIR, exist_ok=True)

HEADERS = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/115.0.0.0 Safari/537.36"
}

def clean_filename(title):
    keepcharacters = (' ', '.', '_', '-')
    return "".join(c for c in title if c.isalnum() or c in keepcharacters).rstrip()

def get_article_links():
    res = requests.get(INDEX_URL, headers=HEADERS)
    res.raise_for_status()
    soup = BeautifulSoup(res.text, 'html.parser')
    
    links = []
    # Find all soundonsound.com links
    for a in soup.find_all('a', href=True):
        href = a['href']
        if "soundonsound.com/techniques/" in href:
            if href not in [l['url'] for l in links]:
                links.append({'url': href, 'title': a.text.strip()})
    
    # Filter list - they are usually numbered in the post, but let's just take unique ones that look like articles.
    # The list contains around 63 articles.
    return links

def download_image(img_url, img_filename):
    img_path = os.path.join(IMG_DIR, img_filename)
    if not os.path.exists(img_path):
        try:
            r = requests.get(img_url, stream=True, headers=HEADERS, timeout=10)
            r.raise_for_status()
            with open(img_path, 'wb') as f:
                for chunk in r.iter_content(1024):
                    f.write(chunk)
            print(f"Downloaded image: {img_filename}")
        except Exception as e:
            print(f"Failed to download image {img_url}: {e}")
    return os.path.join("images", img_filename)

def extract_content(soup):
    # Try different common CSS selectors for main content
    for selector in ['article', 'main', '.node__content', '.content', '#content', '#block-system-main']:
        found = soup.select_one(selector)
        if found:
            # remove navs, headers, footers if inside
            for tag in found.select('nav, header, footer, .sidebar, .comments'):
                tag.decompose()
            return found
    return soup.body

def scrape_article(url, index):
    print(f"Scraping [{index}]: {url}")
    try:
        res = requests.get(url, headers=HEADERS, timeout=10)
        res.raise_for_status()
    except Exception as e:
        print(f"Failed to fetch {url}: {e}")
        return

    soup = BeautifulSoup(res.text, 'html.parser')
    
    # Extract title
    title_tag = soup.find('h1')
    title = title_tag.text.strip() if title_tag else f"Article_{index}"
    safe_title = clean_filename(title)
    
    # Extract main content
    main_content = extract_content(soup)
    if not main_content:
        print(f"Could not find main content for {url}")
        return
        
    # Process images
    for img in main_content.find_all('img'):
        src = img.get('src') or img.get('data-src')
        if not src: continue
        
        abs_src = urljoin(url, src)
        filename = os.path.basename(urlparse(abs_src).path)
        if not filename:
            filename = f"img_{index}_{len(filename)}.jpg"
            
        # Download image and replace src
        local_src = download_image(abs_src, filename)
        img['src'] = local_src
        
        # Remove srcset to force fallback to our local src
        if img.has_attr('srcset'):
            del img['srcset']

    # Convert to markdown
    md = markdownify.markdownify(str(main_content), heading_style="ATX", autolinks=False)
    
    # Clean up empty lines
    md = "\\n".join(line for line in md.splitlines() if line.strip() or line == "")
    
    # Prepend Title and Source
    header = f"# {title}\\n\\n**Source**: [{url}]({url})\\n\\n"
    
    file_path = os.path.join(BASE_DIR, f"{index:02d}_{safe_title}.md")
    with open(file_path, "w", encoding="utf-8") as f:
        f.write(header + md)
        
    print(f"Saved: {file_path}")

def main():
    print("Fetching index...")
    links = get_article_links()
    print(f"Found {len(links)} articles.")
    
    for i, link in enumerate(links, 1):
        scrape_article(link['url'], i)
        
        # Rate limit
        if i < len(links):
            print("Waiting 10 seconds...")
            time.sleep(10)

if __name__ == "__main__":
    main()
