# returning promises for sequential runing child processes

https://stackoverflow.com/questions/42293731/returning-promises-for-sequential-runing-child-processes

```TypeScript
export class RunThingy {
    private curCommand: Promise<string> | null

    private run(options: string[]): Promise<string> {
        let next: Promise<string>
        if (this.curCommand) {
            next = this.curCommand.then(
                () => runCommand(options), // the next command will be started after
                () => runCommand(options)  // the current will be resolved or rejected
            )
        } else
            next = runCommand(options)
        next = next.then(stdout => {
            if (next === this.curCommand) // if this is the last command
                this.curCommand = null    // then forget the current command
            return stdout                 // return the command value
        }, err => {
            if (next === this.curCommand) // if this is the last command
                this.curCommand = null    // then forget the current command
            throw err                     // throw again the error
        })
        this.curCommand = next
        return this.curCommand
    }
}

function runCommand(options: string[]): Promise<string> {
    return new Promise((resolve, reject) => {
        let stdout = '';
        let stderr = '';
        let process: ChildProcess = spawn('processName', options);
        process.stdout.on('data', (contents) => { stdout += contents; });
        process.stderr.on('data', (contents) => { stderr += contents; });
        process
            .on('error', reject)
            .on('close', function (code) {
                if (code === 0) {
                    resolve(stdout);
                } else {
                    reject(new Error(stderr));
                }
            });
    });
}
```
