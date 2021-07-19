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

multibranchPipelineJob('BANG-neutrino-oscillation') {
    branchSources {
        git {
            id('2') // IMPORTANT: use a constant and unique identifier
            remote('https://github.com/snaphu-msu/BANG.git')
            credentialsId('github_personal_access_token')
            includes('nuMixingNotBroken')
        }
    }
}

multibranchPipelineJob('FLASH-MCRHD') {
    branchSources {
        git {
            id('3') // IMPORTANT: use a constant and unique identifier
            remote('https://github.com/srichers/FLASH-MCRHD.git')
            credentialsId('github_personal_access_token')
            includes('*')
        }
    }
}
