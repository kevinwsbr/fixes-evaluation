export default async function ({ addon, console }) {
  // Load scripts from a trusted source or host them locally to prevent XSS attacks
  await addon.tab.loadScript("/path/to/your/local/scripts/linkify.min.js");
  await addon.tab.loadScript("/path/to/your/local/scripts/linkify-element.min.js");

  const pageType = document.location.pathname.substr(1).split("/")[0];

  switch (pageType) {
    case "users":
      document.querySelectorAll("#user-details .read-only").forEach((element) => linkifyElement(element));
      break;

    case "projects":
      (async () => {
        while (true) {
          let element = await addon.tab.waitForElement(".project-description", { markAsSeen: true });
          document.querySelectorAll(".project-description a").forEach((element) => {
            if (/\d+/.test(element.textContent)) element.outerHTML = element.textContent;
          });
          element.normalize();
          linkifyElement(element);
        }
      })();
      break;

    case "studios":
      linkifyElement(document.querySelector("#description.read-only .overview"));
      break;
  }

  (async () => {
    while (true) {
      let comment = await addon.tab.waitForElement(".comment", { markAsSeen: true });
      linkifyElement(comment);
    }
  })();
}
