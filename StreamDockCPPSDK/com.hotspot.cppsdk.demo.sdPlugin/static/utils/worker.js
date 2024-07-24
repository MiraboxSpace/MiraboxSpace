self.onmessage = function (e) {
    setInterval(() => {
        self.postMessage(1)
    }, e.data);
}