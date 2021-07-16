multibranchPipelineJob('FLASH-X') {
    branchSources {
        git {
            id('1') // IMPORTANT: use a constant and unique identifier
            remote('https://github.com/ECP-Astro/FLASH5')
            credentialsId('github_personal_access_token')
            includes('master')
        }
    }
}
