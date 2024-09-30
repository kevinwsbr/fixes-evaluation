export default async function ({ addon, console }) {
  // Load external scripts using a secure protocol
  await addon.tab.loadScript("https://cdn.jsdelivr.net/npm/linkifyjs@2.1.9/dist/linkify.min.js");
  await addon.tab.loadScript("https://cdn.jsdelivr.net/npm/linkifyjs@2.1.9/dist/linkify-element.min.js");

  const pageType = document.location.pathname.substr(1).split("/")[0];

  switch (pageType) {
    case "users":
      // Use a safer way to select elements with the ".read-only" class
      document.querySelectorAll("#user-details .read-only").forEach((element) => linkifyElement(element));
      break;

    case "projects":
      (async () => {
        while (true) {
          let element = await addon.tab.waitForElement(".project-description", { markAsSeen: true });
          // Use a safer way to select elements with the ".project-description" class
          document.querySelectorAll(".project-description").forEach((element) => {
            if (/\d+/.test(element.textContent)) element.outerHTML = element.textContent;
          });
          element.normalize();
          linkifyElement(element);
        }
      })();
      break;

    case "studios":
      // Use a safer way to select elements with the ".read-only" class
      linkifyElement(document.querySelector("#description.read-only .overview"));
      break;
  }

  (async () => {
    while (true) {
      let comment = await addon.tab.waitForElement(".comment", { markAsSeen: true });
      // Use a safer way to select elements with the ".comment" class
      linkifyElement(comment);
    }
  })();
}
