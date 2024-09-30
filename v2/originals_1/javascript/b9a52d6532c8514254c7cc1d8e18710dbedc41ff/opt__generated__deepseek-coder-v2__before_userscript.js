export default async function ({ addon, console }) {
  const trustedSources = [
    "https://cdn.jsdelivr.net/npm/linkifyjs@2.1.9/dist/linkify.min.js",
    "https://cdn.jsdelivr.net/npm/linkifyjs@2.1.9/dist/linkify-element.min.js"
  ];

  for (const source of trustedSources) {
    await addon.tab.loadScript(source);
  }

  const pageType = document.location.pathname.substr(1).split("/")[0];

  switch (pageType) {
    case "users":
      document.querySelectorAll("#user-details .read-only").forEach((element) => linkifyElement(element));
      break;

    case "projects":
      while (true) {
        let element = await addon.tab.waitForElement(".project-description", { markAsSeen: true });
        document.querySelectorAll(".project-description a").forEach((el) => {
          if (/\d+/.test(el.textContent)) el.outerHTML = `<a href="${el.textContent}">${el.textContent}</a>`;
        });
        linkifyElement(element);
      }
      break;

    case "studios":
      linkifyElement(document.querySelector("#description.read-only .overview"));
      break;
  }
}
