multibranchPipelineJob('example') {
    branchSources {
        git {
            id('123456789') // IMPORTANT: use a constant and unique identifier
            remote('git@github.com:ECP-Astro/FLASH5')
            credentialsId('github-ssh')
            includes('master')
        }
    }
}
