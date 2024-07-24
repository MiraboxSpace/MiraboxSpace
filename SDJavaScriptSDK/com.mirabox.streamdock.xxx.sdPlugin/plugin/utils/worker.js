const that = this, Timer = {}

const handle = {
    setTimeout(data) {
        Timer[data.id] = setTimeout(() => {
            that.self.postMessage({
                event: 'setTimeout',
                id: data.id
            })
        }, data.delay)
    },
    setInterval(data) {
        Timer[data.id] = setInterval(() => {
            that.self.postMessage({
                event: 'setInterval',
                id: data.id
            })
        }, data.delay)
    },
    clearTimeout(data) {
        clearTimeout(Timer[data.id])
    },
    clearInterval(data) {
        clearInterval(Timer[data.id])
    }
}

this.self.onmessage = function ({ data }) {
    handle[data?.event]?.(data)
}